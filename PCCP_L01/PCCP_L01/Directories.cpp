#include "Directories.h"


Directories::Directories(unsigned int maxThreads, uintmax_t* resultOnes, uintmax_t* sumSize)
{
	this->maxThreads = maxThreads;
	this->resultOnes = resultOnes;
	this->resultSize = sumSize;
	calculateBits.setMaxThreads(maxThreads);
}

Directories::~Directories()
{
}

void Directories::generateFileTree(vector<string> pathes, vector<string> filter, int maxDepth)
{
	vector<regex> filters;

	splitFilters(filter,&filters);

	for (auto const& _path : pathes) {		//iterate over all pathes
		fs::path path(_path);
		if (filters.size() > 0) {
			getFiles(path, filters, maxDepth);	//get all files
		}
		else {
			getFiles(path, maxDepth);	//get all files
		}
		
	}

	calculateBits.joinThreads();
	//for (auto const& value : files) {
	//	cout << value << endl;
	//}
}

void Directories::getFiles(fs::path path, int maxDepth) {
	maxDepth--;
	fs::directory_iterator end_iter;

	if (fs::exists(path) && fs::is_directory(path))
	{
		try {
			for (fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter)
			{
			
				if (fs::is_regular_file(dir_iter->status()))
				{
					boost::iostreams::mapped_file_source file;
					file.open(dir_iter->path());
					calculateBits.calcBit(&file, this->resultOnes, this->resultSize);
				}
				else if (fs::is_directory(dir_iter->status())) {
					if (maxDepth != -1) {
						getFiles( dir_iter->path(), maxDepth);
					}
				}
			}
		}
		catch (exception e) {
			fprintf(stderr, "Error while Iterating over path %s\n", path.string().c_str());
		}
	}
	else {
		fprintf(stderr, "Error path %s does not exist\n", path.string().c_str());
	}
}

void Directories::getFiles(fs::path path, vector<regex> filters, int maxDepth) {
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
						boost::iostreams::mapped_file_source file;
						file.open(dir_iter->path());
						calculateBits.calcBit(&file, this->resultOnes, this->resultSize);
						break;
					}
				}
			}
			else if (fs::is_directory(dir_iter->status())) {
				if (maxDepth != -1) {
					getFiles(dir_iter->path(), filters, maxDepth);
				}
			}
		}
	}
	else {
		fprintf(stderr, "Error path %s does not exist\n", path.string().c_str());
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
