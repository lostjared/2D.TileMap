use rs_catgfx::catgfx::*;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use tilemap::tile_map::*;

/// draw map
fn draw_map(
    can: &mut sdl2::render::WindowCanvas,
    cam: &Camera,
    tmap: &TileMap,
    textures: &Vec<sdl2::render::Texture>,
) {
    let tsize = 16;
    let start_col = cam.x / tsize;
    let end_col = start_col + (cam.width / tsize);
    let start_row = cam.y / tsize;
    let end_row = start_row + (cam.height / tsize);
    let cx = cam.x;
    let cy = cam.y;
    let off_x = -cx + start_col * tsize;
    let off_y = -cy + start_row * tsize;
    let mut x = 0;
    let mut y = 0;
    x = start_col;
    while x < end_col {
        y = start_row;
        while y < end_row {
            let tile = tmap.at(x, y);
            if x >= 0 && x < tmap.width && y >= 0 && y < tmap.height {
                let tile = &tmap.tiles[x as usize][y as usize];
                let xx: i32 = (x - start_col) * tsize + off_x;
                let yy: i32 = (y - start_row) * tsize + off_y;
                if tile.solid != 2 && tile.solid != 3 {
                    can.copy(
                        &textures[tile.img as usize],
                        sdl2::rect::Rect::new(0, 0, 16, 16),
                        sdl2::rect::Rect::new(xx, yy, 16, 16),
                    )
                    .expect("on copy");
                }
            }
            y += 1;
        }
        x += 1;
    }
}

/// build table of surfaces
fn build_map(filename: &str) -> Vec<sdl2::surface::Surface> {
    let mut table: GfxTable = GfxTable::new();
    build_gfx(filename, &mut table).expect("building graphics table");
    let mut surf: Vec<sdl2::surface::Surface> = Vec::new();
    // load graphics
    for i in &table.items {
        let mut rwops = sdl2::rwops::RWops::from_bytes(i.data.as_slice()).unwrap();
        let s = sdl2::surface::Surface::load_bmp_rw(&mut rwops).unwrap();
        surf.push(s);
    }
    surf
}

/// main function
fn main() -> std::io::Result<()> {
    let args: Vec<String> = std::env::args().collect();

    if args.len() != 3 {
        panic!("Requires two arguments");
    }

    let mut tmap: TileMap = TileMap::new();
    tmap.load_map(&args[1])?;

    println!(
        "Map loaded: [{}] - {}x{}",
        tmap.name, tmap.width, tmap.height
    );

    let surfaces: Vec<sdl2::surface::Surface> = build_map(&args[2]);
    println!("Images loaded: {}", surfaces.len());

    let max_x = tmap.width * 16 - 1280 - 1;
    let max_y = tmap.height * 16 - 720 - 1;
    let mut cam: Camera = Camera::new(1280, 720, max_x, max_y);

    let width = 1280;
    let height = 720;
    let sdl = sdl2::init().unwrap();
    let video = sdl.video().unwrap();
    let window = video
        .window("Tile Demo", width, height)
        .resizable()
        .opengl()
        .build()
        .unwrap();
    let mut can = window
        .into_canvas()
        .build()
        .map_err(|e| e.to_string())
        .expect("Error on canvas");

    let tc = can.texture_creator();
    let mut textures: Vec<sdl2::render::Texture> = Vec::new();

    for mut i in surfaces {
        i.set_color_key(true, sdl2::pixels::Color::RGBA(255, 255, 255, 255))
            .expect("on set color key");
        let tex = tc.create_texture_from_surface(i).unwrap();
        textures.push(tex);
    }

    let mut e = sdl.event_pump().unwrap();
    'main: loop {
        for _event in e.poll_iter() {
            match _event {
                Event::Quit { .. }
                | Event::KeyDown {
                    keycode: Some(Keycode::Escape),
                    ..
                } => break 'main,
                _ => {}
            }
        }
        can.clear();
        draw_map(&mut can, &cam, &tmap, &textures);
        can.present();
    }
    Ok(())
}
