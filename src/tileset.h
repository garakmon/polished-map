#ifndef TILESET_H
#define TILESET_H

#include <string>

#include "tile.h"
#include "palette-map.h"
#include "tiled-image.h"
#include "utils.h"

#define TILES_PER_ROW 16
#define TILES_PER_COL (MAX_NUM_TILES / TILES_PER_ROW)

#define FIRST_ROOF_TILE_ID 0x0a
#define NUM_ROOF_TILES 9
#define ROOF_TILES_PER_ROW 3
#define ROOF_TILES_PER_COL (NUM_ROOF_TILES / ROOF_TILES_PER_ROW)

class Tileset {
public:
	enum Result { GFX_OK, GFX_NO_PALETTE, GFX_BAD_FILE, GFX_BAD_EXT, GFX_BAD_DIMS,
		GFX_TOO_SHORT, GFX_TOO_LARGE, GFX_NOT_GRAYSCALE, GFX_BAD_CMD, GFX_NULL };
private:
	std::string _name, _roof_name;
	Lighting _lighting;
	Palette_Map _palette_map;
	Tile *_tiles[MAX_NUM_TILES], *_roof_tiles[MAX_NUM_TILES];
	size_t _num_tiles, _num_roof_tiles;
	Result _result;
	bool _modified, _modified_roof;
public:
	Tileset();
	~Tileset();
	inline const char *name(void) const { return _name.c_str(); }
	inline void name(const char *m) { _name = m ? m : ""; }
	inline const char *roof_name(void) const { return _roof_name.c_str(); }
	inline void roof_name(const char *m) { _roof_name = m ? m : ""; }
	inline bool has_roof(void) const { return !_roof_name.empty(); }
	inline Lighting lighting(void) const { return _lighting; }
	inline Palette_Map &palette_map(void) { return _palette_map; }
	inline Tile *tile(uint8_t i) { return _tiles[i]; }
	inline Tile *roof_tile(uint8_t i) { return _roof_tiles[i]; }
	inline const Tile *const_tile(uint8_t i) const { return _tiles[i]; }
	inline const Tile *const_roof_tile(uint8_t i) const { return _roof_tiles[i]; }
	inline const Tile *const_tile_or_roof(uint8_t i) const {
		return (i >= FIRST_ROOF_TILE_ID && (size_t)i < FIRST_ROOF_TILE_ID + _num_roof_tiles) ? _roof_tiles[i] : _tiles[i];
	}
	inline size_t num_tiles(void) const { return _num_tiles; }
	inline size_t num_roof_tiles(void) const { return _num_roof_tiles; }
	inline Result result(void) const { return _result; }
	inline bool modified(void) const { return _modified; }
	inline void modified(bool m) { _modified = m; }
	inline bool modified_roof(void) const { return _modified_roof; }
	inline void modified_roof(bool m) { _modified_roof = m; }
private:
	void read_tile(Tile *t, const Tiled_Image &ti, uint8_t i, size_t j);
	void print_tile_rgb(const Tile *t, int tx, int ty, int n, uchar *buffer) const;
public:
	void clear(void);
	void clear_roof_graphics(void);
	void update_lighting(Lighting l);
	uchar *print_rgb(size_t w, size_t h, size_t n) const;
	uchar *print_roof_rgb(size_t w, size_t h) const;
	inline Palette_Map::Result read_palette_map(const char *f) { return _palette_map.read_from(f); }
	Result read_graphics(const char *f, Lighting l);
	Result read_roof_graphics(const char *f);
	static const char *error_message(Result result);
	bool write_graphics(const char *f);
	bool write_roof_graphics(const char *f);
};

#endif
