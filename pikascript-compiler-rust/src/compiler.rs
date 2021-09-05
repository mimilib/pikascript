use crate::class_info::ClassInfo;
use crate::script::Script;
use std::collections::BTreeMap;
use std::fs::File;
use std::io::prelude::*;
#[derive(Debug)]
pub struct Compiler {
    pub dist_path: String,
    pub source_path: String,
    pub class_list: BTreeMap<String, ClassInfo>,
    pub class_now_name: Option<String>,
}

impl Compiler {
    pub fn new(source_path: String, dist_path: String) -> Compiler {
        let compiler = Compiler {
            dist_path: dist_path.clone(),
            source_path: source_path.clone(),
            class_now_name: None,
            class_list: BTreeMap::new(),
        };
        return compiler;
    }
    pub fn analyze_main_line(mut compiler: Compiler, line: String) -> Compiler {
        let file_name = "main".to_string();
        let class_name = "PikaMain".to_string();
        let class_now = match compiler.class_list.get_mut(&"PikaMain".to_string()) {
            Some(class_now) => class_now,
            None => compiler.class_list.entry(class_name.clone()).or_insert(
                ClassInfo::new(
                    &file_name,
                    &"class PikaMain(PikaStdLib.SysObj):".to_string(),
                )
                .unwrap(),
            ),
        };
        compiler.class_now_name = Some(class_name.clone());

        if line.starts_with("def ") {
            class_now.push_method(line);
            return compiler;
        }
        if line.contains("(") && line.contains(")") && line.contains("=") {
            if Script::assert(class_now, &line) {
                class_now.script_list.add(&line);
                return compiler;
            }
            class_now.push_object(line, &file_name);
            return compiler;
        }
        if line.contains("(") && line.contains(")") {
            class_now.script_list.add(&line);
        }
        return compiler;
    }

    pub fn analyze_file(mut compiler: Compiler, file_name: String) -> Compiler {
        println!("analyzing file: {}{}.py", compiler.source_path, file_name);
        let mut file = File::open(format!("{}{}.py", compiler.source_path, file_name)).unwrap();
        let mut file_str = String::new();
        file.read_to_string(&mut file_str).unwrap();
        let lines: Vec<&str> = file_str.split('\n').collect();
        /* analyze each line of pikascript-api.py */
        for line in lines.iter() {
            compiler = Compiler::analyze_line(compiler, line.to_string(), &file_name);
        }
        return compiler;
    }

    pub fn analyze_line(mut compiler: Compiler, line: String, file_name: &String) -> Compiler {
        let line = line.replace("\r", "");
        if line.starts_with("import ") {
            let tokens: Vec<&str> = line.split(" ").collect();
            let file = tokens[1];
            return Compiler::analyze_file(compiler, file.to_string());
        }

        if line.starts_with("#") {
            return compiler;
        }

        if line.starts_with("class") {
            let class_now = match ClassInfo::new(&file_name, &line) {
                Some(s) => s,
                None => return compiler,
            };
            let class_name = class_now.this_class_name.clone();
            compiler
                .class_list
                .entry(class_name.clone())
                .or_insert(class_now);
            compiler.class_now_name = Some(class_name.clone());
            return compiler;
        }
        if line.starts_with("    def ") {
            let line = line.strip_prefix("    ").unwrap().to_string();
            let class_now = compiler
                .class_list
                .get_mut(&compiler.class_now_name.clone().unwrap())
                .unwrap();
            class_now.push_method(line);
            return compiler;
        }
        if line.starts_with("    ")
            && line.contains("(")
            && line.contains(")")
            && line.contains("=")
        {
            let line = line.strip_prefix("    ").unwrap().to_string();
            let class_now = compiler
                .class_list
                .get_mut(&compiler.class_now_name.clone().unwrap())
                .unwrap();
            class_now.push_object(line, &file_name);
            return compiler;
        }
        if line.starts_with("    ") && line.contains("(") && line.contains(")") {
            let line = line.strip_prefix("    ").unwrap().to_string();
            let class_now = compiler
                .class_list
                .get_mut(&compiler.class_now_name.clone().unwrap())
                .unwrap();
            class_now.push_import(line, &file_name);
            return compiler;
        }

        if file_name == "main" {
            return Compiler::analyze_main_line(compiler, line);
        }

        return compiler;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_analyze() {
        let compiler = Compiler::new(String::from(""), String::from(""));
        let compiler = Compiler::analyze_line(
            compiler,
            String::from("class Test(SuperTest):"),
            &"Pkg".to_string(),
        );
        let compiler =
            Compiler::analyze_line(compiler, String::from("    def test()"), &"Pkg".to_string());
        let compiler = Compiler::analyze_line(
            compiler,
            String::from("    testObj = TestObj()"),
            &"Pkg".to_string(),
        );
        let compiler = Compiler::analyze_line(
            compiler,
            String::from("    TestImport()"),
            &"Pkg".to_string(),
        );

        let class_info = compiler.class_list.get("Pkg_Test").unwrap();
        let method_info = class_info.method_list.get("test").unwrap();
        let object_info = class_info.object_list.get("testObj").unwrap();
        let import_info = class_info.import_list.get("Pkg_TestImport").unwrap();
        assert_eq!(class_info.this_class_name, "Pkg_Test");
        assert_eq!(class_info.super_class_name, "Pkg_SuperTest");
        assert_eq!(method_info.name, "test");
        assert_eq!(method_info.class_name, "Pkg_Test");
        assert_eq!(object_info.name, "testObj");
        assert_eq!(object_info.class_name, "Pkg_Test");
        assert_eq!(import_info.class_name, "Pkg_Test");
        assert_eq!(import_info.import_class_name, "Pkg_TestImport");
    }
}
