// limuqing 2021/4/8
// 避免死锁银行家算法的C++ 编程实现
//vscode
#include "stdfax.h"
#include <vector>
const int MAX_process = 50;
const int MAX_source = 30;

int available[MAX_process];				  //各类资源所剩的资源个数
int max_request[MAX_process][MAX_source]; //进程所需要的最大资源数
int alloc[MAX_process][MAX_source];		  //进程n已分配的m资源
int need[MAX_process][MAX_source];		  //进程n所需要的m资源
int request[MAX_process][MAX_source];	  //进程n再次请求的资源

int m, n;
int work[MAX_source];
int finish[MAX_process];
int p[MAX_process];

void init()
{
	cout << "请输入进程数目：" << endl;
	cin >> m;
	cout << "请输入资源种类数：" << endl;
	cin >> n;
	// m = 5;
	// n = 3;
	// alloc[m][n] = {{2, 1, 2},
	// 			   {4, 0, 2},
	// 			   {3, 0, 5},
	// 			   {2, 0, 4},
	// 			   {3, 1, 4}};
	// need[m][n] = {{3, 4, 7},
	// 			  {1, 3, 4},
	// 			  {0, 0, 3},
	// 			  {2, 2, 1},
	// 			  {1, 1, 0}

	// };
	cout << "请按照" << m << "X" << n << "的矩阵格式输入你的进程已分配资源矩阵" << endl;
	for (int j = 0; j < m; ++j)
		for (int i = 0; i < n; ++i)
			cin >> alloc[j][i];

	cout << "请按照" << m << "X" << n << "的矩阵格式输入你的进程仍需要分配资源矩阵" << endl;
	for (int j = 0; j < m; ++j)
		for (int i = 0; i < n; ++i)
			cin >> need[j][i];

	cout << "请输入各个资源现有的数目" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> available[i];
	}
}

//展示各进程的情况
void display()
{
	cout << endl
		 << "---->进程可用的资源为: ";
	for (int i = 0; i < n; i++)
	{
		cout << available[i] << "\t";
	}

	cout << endl
		 << "---->各进程已经分配的资源：" << endl;
	for (int j = 0; j < m; ++j)
	{
		cout << "---->进程" << j + 1 << ":";
		for (int i = 0; i < n; ++i)
			cout << "\t" << alloc[j][i];
		cout << endl;
	}

	cout << endl
		 << "---->各进程仍需要分配的资源：" << endl;
	for (int j = 0; j < m; ++j)
	{
		cout << "---->进程" << j + 1 << ":";
		for (int i = 0; i < n; ++i)
			cout << "\t" << need[j][i];
		cout << endl;
	}
}

//判断是否处于安全状态，并输出安全序列
bool is_safe()
{
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		work[i] = available[i];
	}
	for (int i = 0; i < m; ++i)
	{
		finish[i] = false; //初始化finish数组
	}
	int safeSeq[MAX_process];
	//vector<int> safeSeq;
	int count = 0;
	while (count < m)
	{
		bool found = false;
		for (int p = 0; p < m; ++p)
		{
			if (finish[p] == false)
			{
				int j;
				for (j = 0; j < n; ++j)
					if (need[p][j] > work[j])
						break;

				if (j == n)
				{
					for (int k = 0; k < n; ++k)
						work[k] += alloc[p][k];

					safeSeq[count++] = p + 1; //p+1 是为了进程编号从 1 开始
					//safeSeq.push_back(p);

					finish[p] = true;

					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "系统处于不安全状态！";
			return false;
		}
	}
	cout << "系统处于安全状态！\n"
		 << "安全序列是：";
	for (int i = 0; i < m; ++i)
		cout << safeSeq[i] << " ";
	cout << endl;
	return true;
	// for (int i = 0; i < m; ++i)
	// {
	// 	if (finish[i] == true)
	// 		continue;
	// 	else
	// 	{
	// 		for (j = 0; j < n; ++j)
	// 		{
	// 			if (need[i][j] > work[j])
	// 			{
	// 				break;
	// 			}
	// 		}
	// 		if (j == n)
	// 		{
	// 			finish[i] = true;
	// 			for (int i = 0; i < n; ++i)
	// 			{
	// 				work[j] += alloc[i][j];
	// 			}

	// 			p[l++] = i; //记录进程号
	// 			i = -1;
	// 		}
	// 		else
	// 			continue;
	// 	}
	// }

	// if (l == m)
	// {
	// 	cout << "系统是安全的" << endl;
	// 	cout << "安全序列：" << endl;
	// 	for (int i = 0; i < l; i++)
	// 	{
	// 		cout << p[i];
	// 		if (i != l - 1)
	// 			cout << "-->";
	// 	}
	// 	cout << endl
	// 		 << endl;
	// 	return true;
	// }
	// else
	// 	return false;
}

void banker()
{
	int flag = 0;
	char again;
	int req; //请求进程编号
	while (1)
	{
		display();
		while (true)
		{
			cout << "请输入请求的进程编号：" << endl;
			cin >> req;
			--req;
			if (req > m)
			{
				cout << "没有该进程，请重新输入：" << endl;
				continue;
			}

			cout << "请输入请求的各类资源数" << endl;
			for (int i = 0; i < n; ++i)
				cin >> request[req][i];
			for (int i = 0; i < n; ++i)
			{
				if (request[req][i] > need[req][i])
				{
					cout << "你输入的请求超过了你需要的资源，请重新输入！";
					break;
				}
				if (request[req][i] > available[i])
				{
					cout << "该资源没有那么多！请重新输入！";
					break;
				}
			}
			break;
		}

		//分配资源，更新数组
		for (int i = 0; i < n; ++i)
		{
			available[i] -= request[req][i];
			alloc[req][i] += request[req][i];
			need[req][i] -= request[req][i];
		}

		if (is_safe())
		{
			cout << "满足请求，处于安全状态！" << endl;
		}
		else
		{
			cout << "不能满足你的请求,因为不处于安全状态！" << endl;
			for (int i = 0; i < n; ++i)
			{
				available[i] += request[req][i];
				alloc[req][i] -= request[req][i];
				need[req][i] += request[req][i];
			}
		}

		for (int i = 0; i < n; ++i)
		{
			if (need[req][i] <= 0)
				flag++;
		}
		
		//进程资源全部满足之后，释放资源
		if (flag == n)
		{
			for (int i = 0; i < n; ++i)
			{
				available[i] += alloc[req][i];
				alloc[req][i] = 0;
				need[req][i] = 0;
			}
		}

		//重置 finish 数组，以便进行下一次 safe 判断
		for (int i = 0; i < m; i++)
			finish[i] = false;

		//判断是否继续申请
		cout << "你还想再次请求分配吗？是请按Y/y，否请按N/n！" << endl;
		cin >> again;
		if (again == 'Y' || again == 'y')
			continue;
		else if (again == 'N' || again == 'n')
			break;
		else
			break;
	}
}

int main()
{
	init();
	display();
	is_safe();
	banker();
	system("pause");
}
