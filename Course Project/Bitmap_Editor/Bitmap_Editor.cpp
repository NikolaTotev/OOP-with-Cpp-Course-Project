#include  "CommandParser.h"
#include <filesystem>
namespace fs = experimental::filesystem;

int main(int argc,char *argv[])
{
	CommandParser parser;
	parser.parse_input(argc, argv);
	parser.execute_jobs();	
}
