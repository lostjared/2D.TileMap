use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use tilemap::tile_map::*;

fn main() -> std::io::Result<()> {

    let args : Vec<String> = std::env::args().collect();

    if args.len() != 2 {
        panic!("Requires one argument");
    }

    let mut tmap : TileMap = TileMap::new();
    tmap.load_map(&args[1])?;

    let width = 1280;
    let height = 720;
    let sdl = sdl2::init().unwrap();
    let video = sdl.video().unwrap();
    let window = video.window("Tile Demo", width, height).resizable().opengl().build().unwrap();
    let mut can = window.into_canvas().build().map_err(|e| e.to_string()).expect("Error on canvas");
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
        can.present();
    }
    Ok(())
}