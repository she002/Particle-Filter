//name: Sihan He
//SID: 861000110

#include "grid.h"
#include <utility>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
	if(argc > 3 || argc <= 1)
	{
		cout<<"plaease follow format a.out n m"<<endl;
	}
	srand(time(NULL));
	int n = (int)(argv[1][0]-'0');
	int m = (int)(argv[2][0]-'0');
	//cout<<"0"<<endl;
	map<pair<int, int>, int>NumS;
	for(int i = 0; i < n; i++)
	{
		for( int j = 0; j < n; j++)
		{
			NumS[pair<int, int>(i, j)] = 0;
		}
	}
	//cout<<"1"<<endl;
	Grid map_grid(n, m);
	vector<pair<int, int> >objs;
	int pos_x = rand()%n;
	int pos_y = rand()%n;
	cout<<pos_x<<" "<<pos_y<<endl;
	objs.push_back(pair<int, int>(pos_x, pos_y));
	map_grid[pair<int, int>(pos_x, pos_y)].start = true;
	for(int i = 0; i < n; i++)
	{
			//cout<<"2"<<endl;
			bool made = false;
			while(!made)
			{	
				int pos_x = rand()%n;
				int pos_y = rand()%n;
				pair<int, int>p(pos_x, pos_y);
				made = true;
				for(int j = 0; j < objs.size(); j++)
				{
					if(objs[i] == p)
					{
						made = false;
					}
				}
				if(made == true)
				{
					objs.push_back(p);
					map_grid[p].type = GridCell::OBSTACLE;
				}
			}	
		
	}

	for(int i = 0; i < m; i++)
	{
			//cout<<"2"<<endl;
			bool made = false;
			while(!made)
			{	
				int pos_x = rand()%n;
				int pos_y = rand()%n;
				pair<int, int>p(pos_x, pos_y);
				made = true;
				for(int j = 0; j < objs.size(); j++)
				{
					if(objs[i] == p)
					{
						made = false;
					}
				}
				if(made == true)
				{
					objs.push_back(p);
					map_grid[p].type = GridCell::TERMINAL;
					map_grid[p].policy.second = 10;
				}
			}	
		
	}

	for(int i = 0; i < m; i++)
	{
			cout<<"2"<<endl;
			bool made = false;
			while(!made)
			{	
				int pos_x = rand()%n;
				int pos_y = rand()%n;
				pair<int, int>p(pos_x, pos_y);
				made = true;
				for(int j = 0; j < objs.size(); j++)
				{
					if(objs[i] == p)
					{
						made = false;
					}
				}
				if(made == true)
				{
					objs.push_back(p);
					map_grid[p].type = GridCell::TERMINAL;
					map_grid[p].policy.second = -10;
				}
			}	
		
	}
	//pair<int, int>start(3, 0);
	//pair<int, int>terminal1(0,3);
	//pair<int, int>terminal2(3,3);
	//pair<int, int>pos(2,1);
	//GridCell obs = GridCell();
	//obs.type = GridCell::OBSTACLE;
	//map_grid[pos].type = GridCell::OBSTACLE;
	//map_grid[terminal1].policy.second = 10;
	//map_grid[terminal1].type = GridCell::TERMINAL;
	//map_grid[terminal2].policy.second = -10;
	//map_grid[terminal2].type = GridCell::TERMINAL;
	//map_grid[start].start = true;
	map_grid.print();

	int iterations = 0;
	
	Direction dir = NORTH;
	while(iterations < 10000)
	{
		int cur_x = objs[0].first;
		int cur_y = objs[0].second;
		int next_x, next_y;
		bool found = false;
		bool get_dir = false;
		while(!get_dir)
		{
			int i = (rand()+rand()%10)%4;
			//cout<<rand()<<endl;
			if(i == 0)
			{
				dir = NORTH;
				//cout<<"North"<<endl;
				next_y = cur_y - 1;
				next_x = cur_x;
			}
			else if(i == 1)
			{
				//cout<<"Souch"<<endl;
				dir = SOUTH;
				next_y = cur_y + 1;	
				next_x = cur_x;
			}
			else if(i == 2)
			{
				//cout<<"East"<<endl;
				dir = EAST;
				next_x = cur_x + 1;
				next_y = cur_y;
			}
			else
			{
				//cout<<"West"<<endl;
				dir = WEST;
				next_x = cur_x - 1;
				next_y = cur_y;
			}
			get_dir = true;
			if((next_y > n-1 || next_y < 0)
				||(next_x > n-1 || next_x < 0)
				||(map_grid[pair<int, int>(next_y, next_x)].type == GridCell::OBSTACLE)
				||(map_grid[pair<int, int>(next_y, next_x)].policy.second < 0))
			{
				get_dir = false;
			}
		}
		int count = 0;
		while(!found)
		{
			
			//cout<<cur_y<<" "<<cur_x<<endl;
			pair<int, int>cur_s(cur_y, cur_x);
			pair<int, int>forward_s;
			if(dir == NORTH)
			{
				next_y = cur_y - 1;
				next_x = cur_x;
			}
			else if(dir == SOUTH)
			{
				next_y = cur_y + 1;
				next_x = cur_x;
			}
			else if(dir == EAST)
			{
				next_y = cur_y;
				next_x = cur_x + 1;
			}
			else 
			{
				next_y = cur_y;
				next_x = cur_x - 1;
			}
			//cout<<next_y<<" "<<next_x<<endl;
			forward_s = pair<int, int>(next_y, next_x);
			NumS[cur_s] += 1;
			if(map_grid[cur_s].type == GridCell::TERMINAL)
			{
				found = true;
				//cout<<"found"<<endl;
				break;
			}
			
			double u_c, u_f, u_l, u_r; 
			if(dir == EAST || dir == WEST)
			{
				//cout<<"In E&W"<<endl;
				if(cur_y - 1 < 0 || map_grid[pair<int, int>(cur_y-1, cur_x)].type == GridCell::OBSTACLE)
				{
					//cout<<1<<endl;
					u_l = 0;
				}
				else
				{
					//cout<<2<<endl;
					u_l = map_grid[pair<int, int>(cur_y-1, cur_x)].policy.second;
				}
				if(cur_y + 1 > n-1 || map_grid[pair<int, int>(cur_y+1, cur_x)].type == GridCell::OBSTACLE)
				{
					//cout<<3<<endl;
					u_r = 0;
				}
				else
				{
					//cout<<4<<endl;
					u_r = map_grid[pair<int, int>(cur_y+1, cur_x)].policy.second;
				}
			}
			else if(dir == NORTH || dir == SOUTH)
			{
				//cout<<"In N&S"<<endl;
				if(cur_x - 1 < 0 || map_grid[pair<int, int>(cur_y, cur_x-1)].type == GridCell::OBSTACLE)
				{
					//cout<<1<<endl;
					u_l = 0;
				}
				else
				{
					//cout<<2<<endl;
					u_l = map_grid[pair<int, int>(cur_y, cur_x-1)].policy.second;
				}
				
				if(cur_x + 1 > n-1 || map_grid[pair<int, int>(cur_y, cur_x+1)].type == GridCell::OBSTACLE)
				{
					//cout<<3<<endl;
					u_r = 0;
				}
				else
				{
					//cout<<4<<endl;
					u_r = map_grid[pair<int, int>(cur_y, cur_x+1)].policy.second;
				}
				//cout<<u_l<<" "<<u_r<<endl;
			}


			if((forward_s.first >= 0 || forward_s.first < n)
				&& (forward_s.second >= 0 || forward_s.second < n) )
			{
				double tmp_u_c = map_grid[cur_s].policy.second;
				u_c = 0.8*map_grid[forward_s].policy.second+ 0.1*u_r + 0.1*u_l;
				u_c = u_c + (map_grid[cur_s].reward + map_grid[forward_s].policy.second - u_c)/((double)(NumS[cur_s]+1));
				if(tmp_u_c > u_c)	
				{
					u_c = tmp_u_c;
				}
				map_grid[cur_s].policy.second = u_c;
				
			}
			cur_x = next_x;
			cur_y = next_y;
			bool next_dir = false;
			bool no_dir = false;
			vector<bool>checker(3, true);
			while(!next_dir && !no_dir)
			{
				if(dir == NORTH)
				{
					int i = (rand()+rand()%10)%3;
					if(i == 0) //North
					{
						if(cur_y - 1 >=0 && map_grid[pair<int, int>(cur_y - 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y - 1, cur_x)].policy.second >= 0)
						{
							next_dir = true;
							dir = NORTH;
							//cout<<"go North"<<endl;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else if(i == 1) //West
					{
						if(cur_x - 1 >=0 && map_grid[pair<int, int>(cur_y, cur_x-1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x-1)].policy.second >= 0)
						{
							//cout<<"go West"<<endl;
							next_dir = true;
							dir = WEST;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else //East
					{
						if(cur_x + 1 <= n-1 && map_grid[pair<int, int>(cur_y, cur_x+1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x+1)].policy.second >= 0)
						{
							next_dir = true;
							//cout<<"go East"<<endl;
							dir = EAST;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
				}
				else if(dir == SOUTH)
				{

					int i = (rand()+rand()%10)%3;
					if(i == 0) //south
					{
						if(cur_y + 1 <= n-1 && map_grid[pair<int, int>(cur_y + 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y + 1, cur_x)].policy.second >= 0)
						{
							//cout<<"go South"<<endl;
							next_dir = true;
							dir = SOUTH;
						}	
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else if(i == 1) //West
					{
						if(cur_x - 1 >=0 && map_grid[pair<int, int>(cur_y, cur_x-1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x-1)].policy.second >= 0)
						{
							//cout<<"go west"<<endl;
							next_dir = true;
							dir = WEST;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else //East
					{
						if(cur_x + 1 <= n-1 && map_grid[pair<int, int>(cur_y, cur_x+1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x+1)].policy.second >= 0)
						{
							//cout<<"go east"<<endl;
							next_dir = true;
							dir = EAST;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
				}
				else if(dir == EAST)
				{

					int i = (rand()+rand()%10)%3;
					if(i == 0) //EAST
					{
						if(cur_x + 1 <= n-1 && map_grid[pair<int, int>(cur_y, cur_x+1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x+1)].policy.second >= 0)
						{
							//cout<<"go East"<<endl;
							next_dir = true;
							dir = EAST;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else if(i == 1) //NORTH
					{
						if(cur_y - 1 >=0 && map_grid[pair<int, int>(cur_y - 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y - 1, cur_x)].policy.second >= 0)
						{
							//cout<<"go North"<<endl;
							next_dir = true;
							dir = NORTH;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else //South
					{
						if(cur_y + 1 <= n-1 && map_grid[pair<int, int>(cur_y + 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y + 1, cur_x)].policy.second >= 0)
						{
							//cout<<"go South"<<endl;
							next_dir = true;
							dir = SOUTH;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
				}
				else
				{
					int i = (rand()+rand()%10)%3;
					if(i == 0) //West
					{
						if(cur_x - 1 >= 0 && map_grid[pair<int, int>(cur_y, cur_x-1)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y, cur_x-1)].policy.second >= 0)
						{
							//cout<<"go West"<<endl;
							next_dir = true;
							dir = WEST;
						}
						else
						{
							checker[i] = false;
	
							//cout<<i<<" false"<<endl;
						}
					}
					else if(i == 1) //NORTH
					{
						if(cur_y - 1 >=0 && map_grid[pair<int, int>(cur_y - 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y - 1, cur_x)].policy.second >= 0)
						{
							//cout<<"go North"<<endl;
							next_dir = true;
							dir = NORTH;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}
					else //South
					{
						if(cur_y + 1 <= n-1 && map_grid[pair<int, int>(cur_y + 1, cur_x)].type != GridCell::OBSTACLE
						 && map_grid[pair<int, int>(cur_y + 1, cur_x)].policy.second >= 0)
						{
							//cout<<"go South"<<endl;
							next_dir = true;
							dir = SOUTH;
						}
						else
						{
							checker[i] = false;
							//cout<<i<<" false"<<endl;
						}
					}

					
					
				}
				no_dir = true;
				for(int i = 0; i < checker.size(); i++)
					{
						if(checker[i] == true)
						{	
							no_dir = false;
						}
					}
				
				//count++;
			}
			if(no_dir) found = true;
			//u_s = 0.8*u_f + 0.1*u_l + 0.1*u_r;
		}
		iterations++;
		
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(map_grid[pair<int, int>(i,j)].type == GridCell::BLANK){
				vector<pair<int, int> >mylist;
				pair<int, int>Cur(i, j);
				pair<int, int>North(i-1, j);
				pair<int, int>South(i+1, j);
				pair<int, int>West(i, j-1);
				pair<int, int>East(i, j+1);
				mylist.push_back(North);
				mylist.push_back(South);
				mylist.push_back(West);
				mylist.push_back(East);
				double tmp = 0;
				double dir_num;
				for(int k = 0; k < mylist.size(); k++)
				{
				
					if((mylist[k].first >= 0 && mylist[k].first < n) 
					&&(mylist[k].second >= 0 && mylist[k].second < n))
					{
						if(map_grid[mylist[k]].policy.second > tmp)
						{
							tmp = map_grid[mylist[k]].policy.second;
							dir_num = k;
						}
					}
				}
				//cout<<dir_num<<endl;
				if(dir_num == 0)
				{
					map_grid[Cur].policy.first = NORTH;
				}
				else if(dir_num == 1)
				{
					map_grid[Cur].policy.first = SOUTH;
				}
				else if(dir_num == 2)
				{
					map_grid[Cur].policy.first = WEST;
				}
				else
				{
					map_grid[Cur].policy.first = EAST;
				}
			}		
		}
	}
	map_grid.print();
	return 0;

}
