#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>
#include <cstdlib>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

std::vector<std::string> splite(const std::string &str, const std::string &c)
{
	std::vector<std::string> result;
	std::string::size_type pos1, pos2;
	
	pos1 = 0;
	pos2 = str.find(c);

	while(std::string::npos != pos2)
	{
		std::string sub = str.substr(pos1, pos2 - pos1);
		if (!sub.empty())
			result.push_back(str.substr(pos1, pos2 - pos1) );
		pos1 = pos2 + c.size();
		pos2 = str.find(c, pos1);
	}
	if (pos1 != str.length())
		result.push_back(str.substr(pos1));

	return result;
}

int resolve(const char* input)
{
//	std::vector<std::vector<int> > data;
	std::vector<std::string> mountain = splite(input, "\n");
	
	std::vector<std::string>::iterator iter = mountain.begin();
	unsigned int num = atoi((*iter).c_str());
	assert(mountain.size() == num + 1);

	int (*data)[3] = new int[num][3];
	iter ++;
	for( unsigned int i = 0; iter != mountain.end(), i < num; iter ++, i ++)
		sscanf((*iter).c_str(), "%d,%d,%d", &data[i][0], &data[i][1], &data[i][2]);

	int len = 0;

	for(unsigned int i = 0; i < num; i ++)
	{
		if (i == 0)
			len += data[i][2];
		else
		{	
			if ( (data[i][0] <= data[i - 1][1]) && (data[i][2] > data[i - 1][2]))
				len = len + data[i][2] -  data[i - 1][2];
			else if (data[i][0] > data[i - 1][1])
				len += data[i][2];
			else
				continue;

		}
	}

	//总长度为 上山的距离*2 + B点坐标。上山的距离和下山的距离一定相同
	len = len * 2 + data[num - 1][1];

	return len;
}

	int main(int argc, char* argv[]) 
	{
		const char* input[] = {
			"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
			"1\n1,2,1\n",
			"2\n1,2,1\n2,3,2",
			"3\n1,2,1\n2,3,2\n3,6,1",
			"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
			"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
			"1\n0,1,1",
			"2\n0,1,1\n2,4,3",
			"3\n0,1,1\n2,4,3\n3,5,1",
			"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
			"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
			//TODO please add more test case here
			
			//ADD
			"4\n2,3,3\n4,6,1\n5,6,2\n6,7,4",
			"2\n2,3,3\n4,5,1\n"
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 21, 13};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
