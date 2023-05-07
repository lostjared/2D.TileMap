
pub mod tile_map {

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

            Ok(())
        }
    }

}