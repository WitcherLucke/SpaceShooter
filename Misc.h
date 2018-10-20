// - Files
int FileExists(const char*path)
{
	FILE*f;
	int err = fopen_s(&f, path, "rb");
	if (err) return 0;
	fclose(f);
	return 1;
}

// - Time
double Time() { return (double)timeGetTime(); }
double TimerTime = 0;
void StartTimer() { TimerTime = Time(); }
double CheckTimer() { return Time() - TimerTime; }

// - Random
float Rand01() { return rand() / float(int(RAND_MAX)); }
float Chance(float prob) { return Rand01() <= prob; }

// - Memory
inline void Malloc(size_t size) { return _aligned_malloc(size, 16); }
inline void*Realloc(void *M, size_t size) { return _aligned_realloc(M, size, 16); }
inline void Free(void*M) { if (!M) return; _aligned_free(M); }

template <class C>
void AddObject(C&object, C*&buffer, int&count, int batch = 32)
{
	if (!(count&(batch - 1))) buffer = (C*)Realloc(buffer, (count + batch) * sizeof(C));
	buffer[count] = object;
	count++;
}
