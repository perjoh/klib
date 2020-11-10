#include <klib/file_io.hpp>
#include <filesystem>
#include <cassert>

namespace klib {
namespace io {

    class Text_file : Resource_file
    {
    public :
        Text_file(const std::string& filename) : Resource_file(filename, std::ios::in)
        { }

        std::string contents()
        {
            std::string str;
            str.resize(this->size());
            read(&str[0], str.size());
            str.push_back('\0');
            return str;
        }

    private :
    }; 

    std::string read_textfile(const char* filename)
    {
        Text_file tf(filename);
        return tf.contents();
    } 

    Resource_file::Resource_file(const std::string& filename, size_t flags)
        : filesize_(0)
    {
        // If RESPATH exists, use it as a path.
        const char* respath = std::getenv("RESPATH"); 
        std::filesystem::path filepath = respath ? std::filesystem::path(respath) / filename 
                                                 : std::filesystem::path(filename);

        flags |= std::ios::ate;

        file_.open(filepath.c_str(), static_cast<std::ios_base::openmode>(flags));
        if (file_.is_open()) {
            filesize_ = static_cast<std::size_t>(file_.tellg());
            file_.seekg(0, std::ios::beg);
        } 
    }

    std::size_t Resource_file::read(void* dest, std::size_t bytes)
    {
        assert(bytes > 0);
        assert(dest);

        auto pos = file_.tellg();
        file_.read(reinterpret_cast<char*>(dest), bytes);
        if (file_.good() || file_.eof()) {
            return file_.tellg() - pos;
        }

        return 0;
    }

    std::size_t Resource_file::size() const
    {
        return filesize_;
    }

    std::istream& Resource_file::stream()
    {
        return file_;
    }

} // namespace io
} // namespace klib
