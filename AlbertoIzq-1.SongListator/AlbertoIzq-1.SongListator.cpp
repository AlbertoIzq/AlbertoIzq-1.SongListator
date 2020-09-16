#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
//#include <cctype> // For using isprint to check if there are strange characters in file/directory names
//#include <typeinfo>
//#include <locale>
//#include <codecvt>

#include "MyUtilities.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace filesys = std::filesystem;

void printHeaderLine();
filesys::path readUserFolder();
void createDirectoriesIndentatedList(filesys::path&, std::ofstream&);
void addDirectoryToIndentatedList(filesys::recursive_directory_iterator&, std::ofstream&);
void createSongsIndentatedList(filesys::path&, std::ofstream&);
void addSongToIndentatedList(filesys::recursive_directory_iterator&, std::ofstream&);

void createDirectoriesIndentatedListFullPath(filesys::path&, std::ofstream&);
void addDirectoryToIndentatedListFullPath(filesys::path&, filesys::recursive_directory_iterator&, std::ofstream&);
void createSongsIndentatedListFullPath(filesys::path&, std::ofstream&);
void addSongToIndentatedListFullPath(filesys::path&, filesys::recursive_directory_iterator&, std::ofstream&);

int main() {
	printHeaderLine();

	filesys::path pathToShow{ "D:\\Musica\\00s classics\\Sean Paul - Get Busy.mp3" };// = "D:\\Musica\\00s classics\\Sean Paul - Get Busy.mp3";
	/*cout << "exists() = " << filesys::exists(pathToShow) << "\n"
		<< "root_name() = " << pathToShow.root_name() << "\n"
		<< "root_path() = " << pathToShow.root_path() << "\n"
		<< "relative_path() = " << pathToShow.relative_path() << "\n"
		<< "parent_path() = " << pathToShow.parent_path() << "\n"
		<< "filename() = " << pathToShow.filename() << "\n"
		<< "stem() = " << pathToShow.stem() << "\n"
		<< "extension() = " << pathToShow.extension() << "\n"
		<< "is_directory() = " << filesys::is_directory(pathToShow);*/

	filesys::path user_path = readUserFolder();
	std::ofstream out_file;
	
		// Create list of indentated directories
		out_file.open("../directoriesIndentatedList.txt");
		if (!out_file.is_open()) {
			return 1;
		}
		createDirectoriesIndentatedList(user_path, out_file);
		out_file.close();

		// Create list of indentated songs
		out_file.open("../songsIndentatedList.txt");
		if (!out_file.is_open()) {
			return 1;
		}
		createSongsIndentatedList(user_path, out_file);
		out_file.close();
		
		// Create list of indentated songs with full path
	out_file.open("../songsIndentatedListFullPath.txt");
	if (!out_file.is_open()) {
		return 1;
	}
	createSongsIndentatedListFullPath(user_path, out_file);
	out_file.close();

	return 0;
}

void printHeaderLine() {
	const std::string left_wrapper{ "|Xx\\__" };
	const std::string right_wrapper = reverseString(left_wrapper);
	const std::string app_name{ "SoNg_LiStAtOr" };
	const std::string app_version{ "1.0" };
	const std::string app_release_date{ "31/01/2020" };
	const std::string app_author{ "Albertroll" };
	const std::string app_description{ "This program creates a text file with a list of all the songs contained within a directory." };
	const int console_width{ 80 };

	cout << centrateText(left_wrapper + app_name + right_wrapper, console_width) << endl
		<< "Version: " << app_version << endl
		<< "Author: " << app_author << endl
		<< "Release date: " << app_release_date << endl
		<< app_description << endl
		<< std::setfill('-') << std::setw(console_width) << "" << std::setfill(' ') << endl;
}

filesys::path readUserFolder() {
	bool user_folder_OK{ false };
	cout << "Write a path name (e.g. \"D:\\Musica\", you may right click + paste it): " << endl;
	filesys::path root_folder;
	while (!user_folder_OK) {
		string root_folder_string;
		std::getline(cin, root_folder_string);
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
		root_folder = root_folder_string;
		if (!filesys::is_directory(root_folder)) {
			std::cout << "Incorrect path, it doesn't exist. Please try again: ";
		}
		else {
			user_folder_OK = true;
		}
	}
	return root_folder;
}

void createDirectoriesIndentatedList(filesys::path& user_path, std::ofstream& out_file) {
	for (auto it_entry = filesys::recursive_directory_iterator(user_path);
		it_entry != filesys::recursive_directory_iterator();
		++it_entry) {
		addDirectoryToIndentatedList(it_entry, out_file);
	}
}

void addDirectoryToIndentatedList(filesys::recursive_directory_iterator& it_entry, std::ofstream& out_file) {
	if (it_entry->is_directory()) {
		const std::wstring directory_name_wstring = it_entry->path().filename().wstring();
		string directory_name_string(directory_name_wstring.begin(), directory_name_wstring.end());
		out_file << std::setw(it_entry.depth() * 3) << "" << directory_name_string << endl;
	}
}

void createSongsIndentatedList(filesys::path& user_path, std::ofstream& out_file) {
	for (auto it_entry = filesys::recursive_directory_iterator(user_path);
		it_entry != filesys::recursive_directory_iterator();
		++it_entry) {
		addSongToIndentatedList(it_entry, out_file);
	}
}

void addSongToIndentatedList(filesys::recursive_directory_iterator& it_entry, std::ofstream& out_file) {
	if (it_entry->is_directory()) {
		const std::wstring directory_name_wstring = it_entry->path().filename().wstring();
		string directory_name_string(directory_name_wstring.begin(), directory_name_wstring.end());
		out_file << std::setw(it_entry.depth() * 3) << "" << "\\\\" << directory_name_string << endl;
	}
	else if (it_entry->is_regular_file()) {
		string entry_extension = it_entry->path().extension().string();
		if (entry_extension == ".mp3" || entry_extension == ".wav") {
			const std::wstring file_name_wstring = it_entry->path().filename().stem().wstring();
			string file_name_string(file_name_wstring.begin(), file_name_wstring.end());
			out_file << std::setw(it_entry.depth() * 3) << "" << file_name_string << endl;
		}
	}
}

void createSongsIndentatedListFullPath(filesys::path& user_path, std::ofstream& out_file) {
	for (auto it_entry = filesys::recursive_directory_iterator(user_path);
		it_entry != filesys::recursive_directory_iterator();
		++it_entry) {
		addSongToIndentatedListFullPath(user_path, it_entry, out_file);
	}
}

void addSongToIndentatedListFullPath(filesys::path& user_path, filesys::recursive_directory_iterator& it_entry, std::ofstream& out_file) {
	if (it_entry->is_directory()) {
		const std::wstring directory_name_wstring = it_entry->path().wstring();
		string directory_name_string(directory_name_wstring.begin(), directory_name_wstring.end());
		eraseSubstring(directory_name_string, user_path.string());
		out_file << std::setw(it_entry.depth() * 4) << "" << directory_name_string << endl;
	}
	else if (it_entry->is_regular_file()) {
		string entry_extension = it_entry->path().extension().string();
		if (entry_extension == ".mp3" || entry_extension == ".wav") {
			const std::wstring file_name_wstring = it_entry->path().filename().stem().wstring();
			string file_name_string(file_name_wstring.begin(), file_name_wstring.end());
			out_file << std::setw(it_entry.depth() * 4) << "" << file_name_string << endl;
		}
	}
}

/*
	filesys::path pathToShow{ pathToShowString };// = "D:\\Musica\\00s classics\\Sean Paul - Get Busy.mp3";
	cout << "exists() = " << filesys::exists(pathToShow) << "\n"
		<< "root_name() = " << pathToShow.root_name() << "\n"
		<< "root_path() = " << pathToShow.root_path() << "\n"
		<< "relative_path() = " << pathToShow.relative_path() << "\n"
		<< "parent_path() = " << pathToShow.parent_path() << "\n"
		<< "filename() = " << pathToShow.filename() << "\n"
		<< "stem() = " << pathToShow.stem() << "\n"
		<< "extension() = " << pathToShow.extension() << "\n"
		<< "is_directory() = " << filesys::is_directory(pathToShow);
	*/