#include "medium.h"
Medium::Medium()
{
	medium_access = true;
	collision = false;
	medium_time_busy =0;
	iterator = 0;
	for (int i = 0; i < 10;i++)
	{
		tab_transmitted_packets[i] = nullptr;
	}
}
Medium::~Medium()
{
}

bool Medium::medium_free()
{
	return medium_access;
}
bool Medium::set_medium_access(bool data)
{

	return medium_access = data;
}
double Medium::show_medium_time_busy()
{
	return medium_time_busy;
}
double Medium::set_medium_time_busy(double busy_time,double clk)
{
	return medium_time_busy = busy_time+clk;
}
bool Medium::show_medium_access()
{
	return medium_access;
}

