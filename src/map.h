#ifndef MAP_H
#define MAP_H

#include <deque>
#include <vector>

#include "utils.h"
#include "map-buttons.h"

#define MAX_HISTORY_SIZE 100

struct Map_Attributes {
public:
	uint8_t group;
	std::string environment;
	std::string landmark;
	std::string palette;
public:
	void clear(void);
};

class Map {
protected:
	struct Map_State {
		std::vector<uint8_t> ids;
		Map_State() : ids() {}
		Map_State(size_t n) : ids(n) {}
	};
public:
	enum Result { MAP_OK, MAP_BAD_FILE, MAP_TOO_SHORT, MAP_TOO_LONG, MAP_NULL };
private:
	Map_Attributes _attributes;
	uint8_t _width, _height;
	Block **_blocks;
	Result _result;
	bool _modified;
	std::deque<Map_State> _history, _future;
public:
	Map();
	~Map();
	inline uint8_t width(void) const { return _width; }
	inline uint8_t height(void) const { return _height; }
	inline Map_Attributes attributes(void) const { return _attributes; }
	void attributes(Map_Attributes a) { _attributes = a; }
	inline uint8_t group(void) const { return _attributes.group; }
	inline void group(uint8_t g) { _attributes.group = g; }
	inline std::string environment(void) const { return _attributes.environment; }
	inline void environment(std::string e) { _attributes.environment = e; }
	inline std::string landmark(void) const { return _attributes.landmark; }
	inline void landmark(std::string l) { _attributes.landmark = l; }
	inline std::string palette(void) const { return _attributes.palette; }
	inline void palette(std::string p) { _attributes.palette = p; }
	inline bool is_outside(void) const {
		return _attributes.environment == "TOWN" || _attributes.environment == "ROUTE" ||
			_attributes.environment == "1" || _attributes.environment == "2"; // TPP:AC uses numbers
	}
	void size(uint8_t w, uint8_t h);
	inline size_t size(void) const { return (size_t)_width * (size_t)_height; }
	inline Block *block(uint8_t x, uint8_t y) const { return _blocks[(size_t)y * _width + (size_t)x]; }
	inline Block *block(size_t i) const { return _blocks[i]; }
	void block(uint8_t x, uint8_t y, Block *b);
	inline Result result(void) const { return _result; }
	inline bool modified(void) const { return _modified; }
	inline void modified(bool m) { _modified = m; }
	inline bool can_undo(void) const { return !_history.empty(); }
	inline bool can_redo(void) const { return !_future.empty(); }
	void clear();
	void remember(void);
	void undo(void);
	void redo(void);
	Result read_blocks(const char *f);
public:
	static const char *error_message(Result result);
};

#endif
