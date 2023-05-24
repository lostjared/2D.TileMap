pub mod tile_map {

    use byteorder::{LittleEndian, ReadBytesExt};
    use std::io::Cursor;
    use std::io::Read;
    use std::io::BufRead;
    use rs_lex::rlex::*;

    #[derive(Debug, Default, PartialEq)]
    #[repr(C)]
    /// TIle struct containing info for the each individual image in the map
    pub struct Tile {
        pub color: u8,
        pub solid: u8,
        pub img: u32,
        pub layers: [u8; 3],
    }
    /// TileMap structure
    pub struct TileMap {
        pub tiles: Vec<Vec<Tile>>,
        pub width: i32,
        pub height: i32,
        pub name: String,
    }

    

    impl TileMap {
        /// create new map
        pub fn new() -> Self {
            TileMap {
                tiles: Vec::new(),
                width: 0,
                height: 0,
                name: String::new(),
            }
        }
        /// load new map from file on Little Endian system
        pub fn load_map(&mut self, file: &str) -> std::io::Result<()> {
            let mut f = std::fs::File::open(file)?;
            let mut buffer: Vec<u8> = Vec::new();
            f.read_to_end(&mut buffer)?;
            let mut r = Cursor::new(buffer);
            let header = r.read_u32::<LittleEndian>()?;
            if header != 0x420 {
                panic!("invalid file format");
            }
            let name_len: u32 = r.read_u32::<LittleEndian>()?;
            let mut index: u32 = 0;
            while index < name_len {
                let ch = r.read_u8()?;
                self.name.push(ch as char);
                index += 1;
            }
            self.width = r.read_i32::<LittleEndian>()?;
            self.height = r.read_i32::<LittleEndian>()?;
            for _i in 0..self.width {
                let mut tilez: Vec<Tile> = Vec::new();
                for _z in 0..self.height {
                    let mut tile = Tile {
                        color: 0,
                        solid: 0,
                        img: 0,
                        layers: [0; 3],
                    };
                    unsafe {
                        let ptr = &mut tile as *mut Tile as *mut u8;
                        let mut buf: &mut [u8] =
                            std::slice::from_raw_parts_mut(ptr, std::mem::size_of::<Tile>());
                        r.read_exact(&mut buf)?;
                        tilez.push(tile);
                    }
                }
                self.tiles.push(tilez);
            }

            Ok(())
        }

        pub fn load_map_text(&mut self, input: &str) -> std::io::Result<()> {

            let file = std::fs::File::open(input)?;
            let mut rd = std::io::BufReader::new(file);

            let mut line : String = String::new();
            rd.read_line(&mut line)?;

            let scan = Scanner::new(&line);
            let tokens: Vec<Box<dyn Token>> = scan.into_iter().collect();

            match_token(&tokens, 0, "map");
            let map_name = tokens[1].get_string();
            println!("Map Name: {}", map_name);
            let map_size = tokens[2].get_string();
            let xpos = map_size.find('x').unwrap();
            let map_width = &map_size[0..xpos];
            let map_height = &map_size[xpos+1..];
            let width: i32 = map_width.parse().unwrap();
            let height: i32 = map_height.parse().unwrap();
            println!("size {}x{}", width, height);       

            self.width = width;
            self.height = height;
            self.name = map_name;

            for _x in 0..width {
                for _y in 0..height {
                    let mut line = String::new();
                    rd.read_line(&mut line)?;
                    let mut items = line.split(' ');
                    let first = items.next();
                    let second = items.next(); 
                    println!("{}", second.unwrap());
                }
            }
            // TODO: continue to break down text

            Ok(())
        }

        /// tile at position in map
        pub fn at(&self, x: i32, y: i32) -> Option<&Tile> {
            if x >= 0 && x < self.width && y >= 0 && y < self.height {
                return Some(&self.tiles[x as usize][y as usize]);
            }
            None
        }

        pub fn solid(&self, x: i32, y: i32) -> Option<u8> {
            let tile = self.at(x, y);
            if tile != None {
                let tile = tile.unwrap();
                return Some(tile.solid);   
            }
            None
        }        
    }

    pub struct Camera {
        pub x: i32,
        pub y: i32,
        pub width: i32,
        pub height: i32,
        pub max_x: i32,
        pub max_y: i32,
        pub speed: i32,
    }

    impl Camera {
        pub fn new(w: i32, h: i32, mx: i32, my: i32) -> Camera {
            Camera {
                x: 0,
                y: 0,
                width: w,
                height: h,
                max_x: mx,
                max_y: my,
                speed: 1280,
            }
        }
        pub fn move_camera(&mut self, delta: f64, dx: i32, dy: i32) {
            let dx_val: f64 = dx as f64 * self.speed as f64 * delta;
            let dy_val: f64 = dy as f64 * self.speed as f64 * delta;
            self.x += dx_val as i32;
            self.y += dy_val as i32;
            self.x = std::cmp::max(0, std::cmp::min(self.x, self.max_x));
            self.y = std::cmp::max(0, std::cmp::min(self.y, self.max_y));
        }
        pub fn reset(&mut self) {
            self.x = 0;
            self.y = 0;
        }
    }
}
