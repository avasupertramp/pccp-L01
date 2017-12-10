#include "Directories.h"

Directories::Directories()
{
}


Directories::~Directories()
{
}

vector<fs::path> Directories::generateFileTree(vector<string> pathes, vector<string> filter, int maxDepth)
{
	vector<regex> filters;
	vector<fs::path> files;		//pathes to files

	splitFilters(filter,&filters);

	for (auto const& _path : pathes) {		//iterate over all pathes
		fs::path path(_path);
		if (filters.size() > 0) {
			getFiles(path, &files, filters, maxDepth);	//get all files
		}
		else {
			getFiles(path, &files, maxDepth);	//get all files
		}
		
	}

	//for (auto const& value : files) {
	//	cout << value << endl;
	//}
	return files;
}

void Directories::getFiles(fs::path path, vector<fs::path> *files,int maxDepth) {
	maxDepth--;
	fs::directory_iterator end_iter;

	if (fs::exists(path) && fs::is_directory(path))
	{
		for (fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter)
		{
			if (fs::is_regular_file(dir_iter->status()))
			{
				files->push_back(dir_iter->path());
			}
			else if (fs::is_directory(dir_iter->status())) {
				if (maxDepth != -1) {
					getFiles(dir_iter->path(), files, maxDepth);
				}
			}
		}
	}
	else {
		fprintf(stderr, "Error path %s does not exist\n", path.string());
	}
}

void Directories::getFiles(fs::path path, vector<fs::path> *files, vector<regex> filters, int maxDepth) {
	maxDepth--;
	fs::directory_iterator end_iter;

	if (fs::exists(path) && fs::is_directory(path))
	{
		for (fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter)
		{
			if (fs::is_regular_file(dir_iter->status()))
			{
				for (auto const& temp : filters) {
					string ha = dir_iter->path().string();
					if (regex_match(ha, temp)) {
						files->push_back(dir_iter->path());
						break;
					}
				}
			}
			else if (fs::is_directory(dir_iter->status())) {
				if (maxDepth != -1) {
					getFiles(dir_iter->path(), files, filters, maxDepth);
				}
			}
		}
	}
	else {
		fprintf(stderr, "Error path %s does not exist\n", path.string());
	}
}

void Directories::splitFilters(vector<string> filters, vector<regex>* returnValue)
{
	for (auto const& value : filters) {
		vector<string>temp;
		boost::split(temp, value, boost::is_any_of(";"));
		for (auto const& filt : temp) {
			string temp = filt;
			temp.insert(temp.find("*"),".");
			regex myReg(temp);
			returnValue->push_back(myReg);
		}
	}
}
