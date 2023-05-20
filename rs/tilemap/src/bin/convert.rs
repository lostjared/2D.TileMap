
use tilemap::tile_map::*;
use std::io::Write;

fn main() -> std::io::Result<()> {
    let args : Vec<String> = std::env::args().collect();
    if args.len() != 3 {
        println!("Requires two arguments\ninput.lvl output.txt");
        std::process::exit(0);
    }
    convert(&args[1], &args[2])?;
    Ok(())
}

fn convert(input: &str, output: &str) -> std::io::Result<()> {
    let mut tmap = TileMap::new();
    tmap.load_map(input)?;
    let ofile = std::fs::File::create(output)?;
    let mut buf = std::io::BufWriter::new(ofile);
    writeln!(buf, "map \"{}\" \"{}x{}\" {{", tmap.name, tmap.width, tmap.height)?;
    for i in 0..tmap.width {
        for z in 0..tmap.height {
            let tile = tmap.at(i, z).unwrap();
            writeln!(buf, "{{ {}, {}, {}, {}, {}, {} }}, ", tile.color, tile.img, tile.solid, tile.layers[0], tile.layers[1], tile.layers[2])?;            
        }
    }
    writeln!(buf, " 0 \n}}")?;
    println!("convert: converted {} to {}", input, output);
    Ok(())
}