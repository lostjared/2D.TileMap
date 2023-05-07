
pub mod tile_map {

    #[repr(C)]
    struct Tile {
        pub color: u8,
        pub solid: u8,
        pub img: u32,
        pub layers: [u8; 3],
    }

    struct TileMap {
        tiles: Vec<Vec<Tile>>,  
    }

    impl TileMap {

        fn new() -> Self {
            TileMap { tiles: Vec::new() }
        }

        fn load_map(&mut self, file: &str) -> std::io::Result<()> {

            Ok(())
        }
    }

}