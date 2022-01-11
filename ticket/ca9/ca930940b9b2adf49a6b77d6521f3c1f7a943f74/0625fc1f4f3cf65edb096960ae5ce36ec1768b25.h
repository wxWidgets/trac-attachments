
class LeftTree1
{
public:
	void left_tree_1();
};

class LeftTree2 : public LeftTree1
{
public:
	void left_tree_2();
};

class RightTree1
{
public:
	void right_tree_1();
};

class RightTree2 : public RightTree1
{
public:
	void right_tree_2();
};

class Joined : public LeftTree2, public RightTree2
{
public:
	void joined();
};

class SubJoined : public Joined
{
public:
	void sub_joined();
};

