use rs_catgfx::catgfx::*;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use tilemap::tile_map::*;

fn draw_map(tmap: &TileMap, surfaces: &Vec<sdl2::surface::Surface>) {}

fn build_map(table: &GfxTable) -> Vec<sdl2::surface::Surface> {
    let surf: Vec<sdl2::surface::Surface> = Vec::new();
    for i in &table.items {}
    surf
}

fn main() -> std::io::Result<()> {
    let args: Vec<String> = std::env::args().collect();

    if args.len() != 3 {
        panic!("Requires one argument");
    }

    let mut tmap: TileMap = TileMap::new();
    tmap.load_map(&args[1])?;

    println!(
        "Map loaded: [{}] - {}x{}",
        tmap.name, tmap.width, tmap.height
    );

    let mut table: GfxTable = GfxTable::new();
    build_gfx(&args[2], &mut table)?;

    let surfaces: Vec<sdl2::surface::Surface> = build_map(&table);
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
        draw_map(&tmap, &surfaces);
        can.present();
    }
    Ok(())
}
