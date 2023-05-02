use clap::{App, Arg};
use rs_catgfx::catgfx::*;


enum Operation {
    Concat,
    Extract,
    List,
    About,
}

struct Arguments {
    source: String,
    dir: Option<String>, 
    input: Option<String>,
    mode: Operation,
}

fn parse_args() -> Arguments {
    let m = App::new("catgfx")
        .version("0.1.0")
        .author("jared")
        .arg(
            Arg::with_name("cat")
                .short('c')
                .long("cat")
                .takes_value(true)
                .required(false)
                .allow_invalid_utf8(true),
        )
        .arg(
            Arg::with_name("extract")
                .short('e')
                .long("extract")
                .takes_value(true)
                .required(false)
                .allow_invalid_utf8(true),
        )
        .arg(
            Arg::with_name("dir")
                .short('d')
                .long("dir")
                .takes_value(true)
                .required(false)
                .allow_invalid_utf8(true),
        )
        .arg(
            Arg::with_name("input")
                .short('i')
                .long("input")
                .takes_value(true)
                .required(false)
                .allow_invalid_utf8(true),
        )
        .arg(
            Arg::with_name("list")
                .short('l')
                .long("list")
                .takes_value(true)
                .required(false)
                .allow_invalid_utf8(true),
        )
        .get_matches();

    let value = m.value_of_lossy("list");
    if value != None {
        return Arguments { source: value.unwrap().to_string(), dir: None,  input: None, mode: Operation::List }
    }

    let value = m.value_of_lossy("extract");
    if value != None {
        let d = m.value_of_lossy("dir").unwrap();
        return Arguments { source: value.unwrap().to_string(),dir: Some(d.to_string()), input: None, mode: Operation::Extract }
    }

    let value = m.value_of_lossy("cat");
    if value != None {
        let c = m.value_of_lossy("input").unwrap();
        return Arguments { source: value.unwrap().to_string(), dir: None, input: Some(c.to_string()), mode: Operation::Concat }
    }

    let input = String::new();
    let m = 0;

    Arguments {
        source: input,
        mode: Operation::About,
        dir: None,
        input: None,
    }
}

fn main() -> std::io::Result<()> {
    let args = parse_args();

    Ok(())
}
