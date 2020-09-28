#include <bits/stdc++.h>
using namespace std;
// 字符串格式化 
bool format(string &str){
	regex e("^(?:(?!0000)[0-9]{4}-(?:(?:0[1-9]|1[0-2])-(?:0[1-9]|1[0-9]|2[0-8])|(?:0[13-9]|1[0-2])-(?:29|30)|(?:0[13578]|1[02])-31)|(?:[0-9]{2}(?:0[48]|[2468][048]|[13579][26])|(?:0[48]|[2468][048]|[13579][26])00)-02-29)$");
	smatch m;
	bool found = regex_search(str, m, e);
	if(found){
		str = str.substr(0,4) + str.substr(5,2) + str.substr(8,2);
		return true;
	}else{
		return false;
	}
}
// 判断是不是闰年 
bool isLeap(int year){
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return true;
	}else{
		return false;
	}
}
int  strTonum(string s){   
    int num;
    stringstream sl(s);
    sl >> num;
    return num;
}
bool isMonth(int month){
	bool flag = false;
	switch(month){
		case 4:flag = true;break;
		case 6:flag = true;break;
		case 9:flag = true;break;
		case 11:flag = true;break;
	}
	return flag;
}
int main(int argc, char** argv) 
{
 
	cout << "请输入你要输入的日期(格式如下:例如是2020-08-01)" << endl;
 	string time;
	bool flag; 
	cin >> time;
	flag = format(time);
	
	if(flag){
		
		// 公共处理
		if(strTonum(time.substr(4,2)) == 12 && strTonum(time.substr(6,2)) == 31){
			time = time.replace(0,4,to_string(strTonum(time.substr(0,4)) + 1));
			time = time.replace(4,4,"0101");
		}else if((isMonth(strTonum(time.substr(4,2))) && strTonum(time.substr(6,2)) == 30 && strTonum(time.substr(4,2)) < 9) || (strTonum(time.substr(6,2)) == 31 && strTonum(time.substr(4,2)) < 9)){
			time = time.replace(5,1,to_string(strTonum(time.substr(5,1)) + 1));
			time = time.replace(6,2,"01");
		}else if((isMonth(strTonum(time.substr(4,2))) && strTonum(time.substr(6,2)) == 30 && strTonum(time.substr(4,2)) >= 9) || (strTonum(time.substr(6,2)) == 31 && strTonum(time.substr(6,2)) >= 9)){
			time = time.replace(4,2,to_string(strTonum(time.substr(4,2)) + 1));
			time = time.replace(6,2,"01");
		}else if(strTonum(time.substr(6,2)) >= 1 && strTonum(time.substr(4,2)) != 2){
			time = time.replace(6,2,to_string(strTonum(time.substr(6,2)) + 1));
		}else{
			if(isLeap(strTonum(time.substr(0,4)))){
				// 处理日期
				if(strTonum(time.substr(4,2)) == 2 && strTonum(time.substr(6,2)) == 28){
					time.at(7) = '9';
				}else if(strTonum(time.substr(4,2)) == 2 && strTonum(time.substr(6,2)) == 29){
					time = time.replace(5,3,"301");
				}
			}else{
				if(strTonum(time.substr(4,2)) == 2 && strTonum(time.substr(6,2)) == 28){
					time = time.replace(5,3,"301");
				}
			}
		}
		cout << "明天的时间为:" << time.substr(0,4) << "年" << time.substr(4,2) << "月" << time.substr(6,2) << "日"<< endl; 
	}else{
		cout << "日期或者日期的格式错误" << endl;
	}

	return 0;
}
