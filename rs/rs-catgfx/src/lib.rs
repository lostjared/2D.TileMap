pub mod catgfx {

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
            GfxItem { index: i, solid: s, obj: o, name: n.to_string() }
        }
    }

    impl GfxTable {
        pub fn new() -> Self {
            GfxTable {
                items: Vec::new(),
            }
        }  

        pub fn add_item(&mut self, item: GfxItem) {
            self.items.push(item);
        }  

        pub fn clear(&mut self) {
            self.items.clear();
        }
    }

    pub fn cat_gfx(table: &GfxTable) -> bool {



        true
    }

    pub fn extract_gfx(table: &GfxTable) -> bool {

        true
    }

    pub fn list_gfx(table: &GfxTable) -> bool {

        true
    }

}