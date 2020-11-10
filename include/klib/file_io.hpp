#pragma once
#include <string>
#include <fstream>

namespace klib {
namespace io {

    std::string read_textfile(const char* filename);

    // 
    class Resource
    {
    public :
        virtual ~Resource() {}

        virtual std::size_t read(void* dest, std::size_t bytes) = 0;

    private :
    };

    // 
    class Resource_file : public Resource
    {
    public : 
        Resource_file(const std::string& filename, size_t flags = std::ios::binary);

    public :
        std::size_t read(void* dest, std::size_t bytes) override;
        std::size_t size() const;

        std::istream& stream();

    private :
        std::ifstream file_;
        std::size_t filesize_;
    };

} // namespace io
} // namespace klib
