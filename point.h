#ifndef POINT
#define POINT
class Point{
private:
	int m_x;
	int m_y;

public:
	Point(int x,int y): m_x{x}, m_y{y}{};

	int getX() const {
		return m_x;
	}

	int getY() const {
		return m_y;
	}
};
#endif