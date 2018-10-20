class Vector2
{
public:
	float x, y;
	float SqrLen() { return x * x + y * y; }
	float Length() { return sqrt(SqrLen()); }
	float SqrDistance(Vector2 v) { return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y); }
	float Distance(Vector2 v) { return sqrt(SqrDistance(v)); }
	void Normalize() { float ilen = 1.0f / Length(); x *= ilen; y *= ilen; }
	void Normalize(float newLen) { float ilen = newLen / Length(); x *= ilen; y *= ilen; }
	void Rotate(float rads)
	{
		float c = cos(rads);
		float s = sin(rads);
		float ox = x, oy = y;
		x = ox * c - oy * s;
		y = ox * s + oy * c;
	}
	Vector2() {}
	Vector2(float x, float y) { this->x = x; this->y = y; }
};

Vector2 operator +(Vector2 v0, Vector2 v1)
{
	return Vector2(v0.x + v1.x, v0.y + v1.y);
}
Vector2 operator -(Vector2 v0, Vector2 v1)
{
	return Vector2(v0.x - v1.x, v0.y - v1.y);
}
Vector2 operator *(Vector2 v0, Vector2 v1)
{
	return Vector2(v0.x*v1.x, v0.y*v1.y);
}
Vector2 operator /(Vector2 v0, Vector2 v1)
{
	return Vector2(v0.x / v1.x, v0.y / v1.y);
}

Vector2 operator *(Vector2 v, float f)
{
	return Vector2(v.x*f, v.y*f);
}
Vector2 operator *(float f, Vector2 v)
{
	return Vector2(v.x*f, v.y*f);
}
Vector2 operator /(Vector2 v, float f)
{
	return Vector2(v.x / f, v.y / f);
}

