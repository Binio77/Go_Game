#ifndef stone_h
#define stone_h
class Stone
{
public:
	bool stone_is_here;
	bool stone_colour;
	Stone *up, *down, *right, *left;
	//Stone();
};

#endif

