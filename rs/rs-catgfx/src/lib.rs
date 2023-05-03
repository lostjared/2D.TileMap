pub mod catgfx {

    use std::io::Cursor;
    use byteorder::{LittleEndian, BigEndian, ReadBytesExt};
    use std::io::Read;

    pub struct GfxItem {
        index: u32,
        solid: u32,
        obj: u32,
        name: String,
    }

    pub struct GfxTable {
        items: Vec<GfxItem>,
    }

    impl GfxItem {
        pub fn new(i: u32, s: u32, o: u32, n: &str) -> Self {
            GfxItem {
                index: i,
                solid: s,
                obj: o,
                name: n.to_string(),
            }
        }
    }

    impl GfxTable {
        pub fn new() -> Self {
            GfxTable { items: Vec::new() }
        }

        pub fn add_item(&mut self, item: GfxItem) {
            self.items.push(item);
        }

        pub fn clear(&mut self) {
            self.items.clear();
        }
    }

    pub fn cat_gfx(input: &str, cfg_file: &str) -> bool {
        println!("catgfx: concat {} with {}", input, cfg_file);
        true
    }

    pub fn extract_gfx(input: &str, output_dir: &str) -> bool {
        println!("catgfx: extract {} to {}", input, output_dir);
        true
    }

    pub fn list_gfx(input: &str) -> bool {
        println!("catgfx: list {}", input);
        let mut f = std::fs::File::open(input).expect("on file open");
        let mut data : Vec<u8> = Vec::new();
        f.read_to_end(&mut data).expect("read");
        let mut reader = Cursor::new(data);
        let header = reader.read_u32::<LittleEndian>().expect("on read");
        if header != 0x421 {
            panic!("Error invalid file type");
        }
        true
    }
}
