use rs_catgfx::catgfx::*;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use tilemap::tile_map::*;

fn draw_map(tmap: &TileMap, textures: &Vec<sdl2::render::Texture>) {}

fn build_map(filename: &str) -> Vec<sdl2::surface::Surface> {
    let mut table: GfxTable = GfxTable::new();
    build_gfx(filename, &mut table).expect("building graphics table");
    let mut surf: Vec<sdl2::surface::Surface> = Vec::new();
    // load graphics
    for i in &table.items {
        let mut rwops = sdl2::rwops::RWops::from_bytes(i.data.as_slice()).unwrap();
        let s= sdl2::surface::Surface::load_bmp_rw(&mut rwops).unwrap();
        surf.push(s);
    }
    surf
}

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
        i.set_color_key(true, sdl2::pixels::Color::RGBA(255, 255, 255, 255)).expect("on set color key");
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
        draw_map(&tmap, &textures);
        can.present();
    }
    Ok(())
}
