// returns s1 if t equals 0
// returns s2 if t equals 1
template <class C>
C Cubic(C s0, C s1, C s2, C s3, float t)
{
	return s1 * (1 + (t - 2)*t*t) + t * (s2 - (t - 1)*((s0 + s2 - s3)*t - s0));
};