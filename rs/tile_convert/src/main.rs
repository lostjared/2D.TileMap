use clap::{App, Arg};
use tilemap::tile_map;

enum OpMode {
    Text2Bin,
    Bin2Text,
}

struct Arguments {
    input: String,
    output: String,
    mode: OpMode,
}

fn parse_args() -> Arguments {
    let m = App::new("tile_convert")
        .arg(
            Arg::new("input")
                .short('i')
                .long("input")
                .required(true)
                .takes_value(true)
                .allow_invalid_utf8(true),
        )
        .arg(
            Arg::new("output")
                .short('o')
                .long("output")
                .takes_value(true)
                .required(true)
                .allow_invalid_utf8(true),
        )
        .arg(Arg::new("bin").short('b').long("bin"))
        .arg(Arg::new("text").short('t').long("text"))
        .get_matches();

    let input_ = m.value_of_lossy("input").unwrap();
    let out_ = m.value_of_lossy("output").unwrap();
    let op_mode;
    if m.is_present("bin") {
        op_mode = OpMode::Bin2Text;
    } else if m.is_present("text") {
        op_mode = OpMode::Text2Bin;
    } else {
        panic!("Required mode info not available use either -t or -b");
    }
    Arguments {
        input: input_.to_string(),
        output: out_.to_string(),
        mode: op_mode,
    }
}

fn main() -> std::io::Result<()> {
    let args = parse_args();
    match args.mode {
        OpMode::Text2Bin => {
            let mut tmap = tile_map::TileMap::new();
            tmap.load_map_text(&args.input)?;
            tmap.save_map(&args.output)?;
            println!(" {} (text) -> {} (bin) ", args.input, args.output);
        }
        OpMode::Bin2Text => {
            let mut tmap = tile_map::TileMap::new();
            tmap.load_map(&args.input)?;
            tmap.save_map_text(&args.output)?;
            println!(" {} (bin) -> {} (text) ", args.input, args.output);
        }
    }
    Ok(())
}
