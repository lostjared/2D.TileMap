pub mod tile_map {

    use byteorder::{LittleEndian, ReadBytesExt};
    use std::io::Cursor;
    use std::io::Read;

    #[derive(Debug, Default)]
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

        /// tile at position in map
        pub fn at(&self, x: i32, y: i32) -> Option<&Tile> {
            if x >= 0 && x < self.width && y >= 0 && y < self.height {
                Some(&self.tiles[x as usize][y as usize]);
            }
            None
        }
    }
}
