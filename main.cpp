#include <iostream>
#include <string>
#include <filesystem>
#include <cctype>

int main() {
    std::string pathInput;
    std::cout << "Enter a path to organize: ";
    std::cin >> pathInput;
    
    const std::filesystem::path path{pathInput};

    for (auto const& dir_entry : std::filesystem::directory_iterator{path}) {
        if (dir_entry.path().has_extension()) {
            std::string ext = dir_entry.path().extension().string().substr(1);
            for (char& c : ext) c = std::toupper(c);

            std::string folder_name = ext + " Files";
            std::filesystem::path ext_folder = path / folder_name;

            if (!std::filesystem::exists(ext_folder)) {
                std::filesystem::create_directory(ext_folder);
            }

            std::filesystem::rename(dir_entry.path(), ext_folder / dir_entry.path().filename());
        }
    }

    return 0;
}
