#include "server/MultiServer.hpp"
#include "ConfigParser/Parser.hpp"
#include "server/CGI/CGI.hpp"

// int main(int argc, char **argv)
// {
// 	ñapaCounter = 0;
//     if (argc != 2) {
//         std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
//         return 1;
//     }
//     std::ifstream inFileStream(argv[1]);

//     if (!inFileStream.is_open()) {
//         std::cerr << "Error: Could not open file " << argv[1] << std::endl;
//         return 1;
//     }

//     std::string buffer;
//     inFileStream.seekg(0, std::ios::end);
//     buffer.resize(inFileStream.tellg());
//     inFileStream.seekg(0, std::ios::beg);
//     inFileStream.read(&buffer[0], buffer.size());
//     inFileStream.close();
//     std::cout << "File content:\n" << buffer << std::endl;

//     try {
//         simpleParser::Tokenizer tokenizer;
//         std::vector<simpleParser::Token> tokens = tokenizer.parse(buffer);
//         for (size_t i = 0; i < tokens.size(); i++) {
//             tokens[i].debugPrint();
//         }
//         simpleParser::Parser parser;
//         parser.parse(tokens);
//         MultiServer multi(parser.getConfigServers());
//         multi.run();
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return -1;
//     }
// }

// int main() {
//     std::string cgi_path = "./cgi_bin/uploader";
//     std::string file_path = "./cgi_bin/upload.sh";
//     std::string file_content = "Esto es el contenido del archivo";
//     Response ret;

//     // Este va a ser el mapa con el que le vamos a pasar todas las variables de entorno.
//     std::map<std::string, std::string> env;
//     env["REQUEST_METHOD"] = "GET";
//     env["SERVER_PROTOCOL"] = "HTTP/1.1";
//     env["PATH_INFO"] = "asdasdasdasdasd";
//     env["filename"] = "vgutten2.txt && (echo hola)";

//     // Este va a ser el vector con el que le vamos a pasar los argumentos.
//     std::vector<std::string> args;
//     args.push_back(cgi_path);
//     args.push_back(file_path);
//     args.push_back(file_content);

//     CGI cgi(cgi_path);
//     cgi.set_env(env);
//     cgi.set_args(args);
//     ret = cgi.run_CGI("Esto sería el body");

//     // std::cout << "Header Status: " << ret.headers["Status"] << std::endl;
//     // std::cout << "Header Status: " << ret.headers["Filename"] << std::endl;

//     std::cout << "Body: " << ret.string_body << std::endl;
//     //Guardamos en ret los valores que obtenemos del CGI.

//     return 0;
// }
