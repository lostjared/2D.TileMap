use tilemap::tile_map::*;

fn main() -> std::io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let mut m = TileMap::new();

    if args.len() != 2 {
        eprintln!("Error invalid arguments....\n");
        std::process::exit(-1);
    }

    m.load_map(&args[1])?;

    Ok(())
}
