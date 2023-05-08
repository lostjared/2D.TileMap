
pub mod tile_map {

    use std::io::Read;
    use byteorder::{LittleEndian, ReadBytesExt};
    use std::io::Cursor;

    #[repr(C)]
    pub struct Tile {
        pub color: u8,
        pub solid: u8,
        pub img: u32,
        pub layers: [u8; 3],
    }

    pub struct TileMap {
        pub tiles: Vec<Vec<Tile>>,
        pub width: i32,
        pub height: i32,
        pub name: String,  
    }

    impl TileMap {

        pub fn new() -> Self {
            TileMap { tiles: Vec::new(), width: 0, height: 0, name: String::new() }
        }

        pub fn load_map(&mut self, file: &str) -> std::io::Result<()> {
            let mut f = std::fs::File::open(file)?;
            let mut buffer : Vec<u8> = Vec::new();
            f.read_to_end(&mut buffer)?;
            let mut r = Cursor::new(buffer);
            let header = r.read_u32::<LittleEndian>()?;
            if header != 0x420 {
                panic!("invalid file format");
            }
            let name_len : u32 = r.read_u32::<LittleEndian>()?;
            let mut index : u32 = 0;
            while index < name_len {
                let ch = r.read_u8()?;
                self.name.push(ch as char);
            }
            Ok(())
        }
    }

}