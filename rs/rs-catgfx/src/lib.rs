pub mod catgfx {

    use std::io::Cursor;
    use byteorder::{LittleEndian,ReadBytesExt};
    use std::io::Read;

    /// Graphics Item
    pub struct GfxItem {
        pub index: u32,
        pub solid: u32,
        pub obj: u32,
        pub name: String,
    }

    /// Graphics Table
    pub struct GfxTable {
        items: Vec<GfxItem>,
    }

    /// implementation of GfxItem
    impl GfxItem {
        /// create new item function
        pub fn new(i: u32, s: u32, o: u32, n: &str) -> Self {
            GfxItem {
                index: i,
                solid: s,
                obj: o,
                name: n.to_string(),
            }
        }
    }

    /// implemtnation of GfxTable
    impl GfxTable {

        /// create new table
        pub fn new() -> Self {
            GfxTable { items: Vec::new() }
        }
        /// add Item to table
        pub fn add_item(&mut self, item: GfxItem) {
            self.items.push(item);
        }
        /// clear table
        pub fn clear(&mut self) {
            self.items.clear();
        }
    }
    /// concat graphics
    pub fn cat_gfx(input: &str, cfg_file: &str) -> std::io::Result<()> {
        println!("catgfx: concat {} with {}", input, cfg_file);
        Ok(())
    }

    /// extract graphics
    pub fn extract_gfx(input: &str, output_dir: &str) -> std::io::Result<()> {
        println!("catgfx: extract {} to {}", input, output_dir);
        Ok(())
    }

    /// list graphics in file
    pub fn list_gfx(input: &str) -> std::io::Result<()> {
        println!("catgfx: list {}", input);
        let mut f = std::fs::File::open(input)?;
        let mut data : Vec<u8> = Vec::new();
        f.read_to_end(&mut data)?;
        let mut reader = Cursor::new(data);
        let header = reader.read_u32::<LittleEndian>()?;
        if header != 0x421 {
            panic!("Error invalid file type");
        }
        Ok(())
    }
}
