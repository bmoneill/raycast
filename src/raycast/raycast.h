#ifndef RAYCAST_H
#define RAYCAST_H

#include <SDL3/SDL.h>
#include <stdint.h>

#ifndef RAYCAST_VERSION
#define RAYCAST_VERSION "unknown"
#endif

/**
 * @brief Raycast color type
 * ARGB (0xAARRGGBB) signed 32-bit integer
 */
typedef int32_t RaycastColor; // ARGB format: 0xAARRGGBB

/**
 * @brief Raycast empty (transparent) color
 */
static const RaycastColor RAYCAST_EMPTY = -1;

/**
 * @brief Raycast direction type
 */
typedef enum { RAYCAST_FORWARD, RAYCAST_BACKWARD, RAYCAST_LEFT, RAYCAST_RIGHT } RaycastDirection;

/**
 * @struct RaycastTexture
 * @brief Texture structure for wall rendering
 */
typedef struct {
    RaycastColor* pixels; //!< ARGB pixel data
    int           width; //!< Width of the texture
    int           height; //!< Height of the texture
} RaycastTexture;

/**
 * @struct RaycastHit
 * @brief Information about a raycast hit
 */
typedef struct {
    float distance; //!< Distance to the hit point
    float wallX; //!< Position where the wall was hit (0.0 to 1.0)
    int   side; //!< Which side of the wall was hit (0 = vertical, 1 = horizontal)
    int   textureId; //!< ID of the texture to use
} RaycastHit;

/**
 * @struct Raycaster
 * @brief Raycaster structure
 */
typedef struct {
    RaycastColor*
        map; //!< 1D array representing the 2D map (RaycastColor if untextured, RaycastTexture if textured)
    int              width; //!< Width of the map
    int              height; //!< Height of the map
    RaycastTexture** textures; //!< Array of textures
    int              textureCount; //!< Number of textures
    int              textured; //!< Whether to use textures
} Raycaster;

/**
 * @struct RaycastRect
 * @brief Raycast rectangle structure
 */
typedef struct {
    float x; //!< X coordinate
    float y; //!< Y coordinate
    float w; //!< Width
    float h; //!< Height
} RaycastRect;

/**
 * @struct RaycastCamera
 * @brief Raycast camera structure
 */
typedef struct {
    float posX; //!< X coordinate
    float posY; //!< Y coordinate
    float dirX; //!< Direction vector x
    float dirY; //!< Direction vector y
    float planeX; //!< Camera plane x
    float planeY; //!< Camera plane y
    int   fov; //!< Field of view in degrees
} RaycastCamera;

float           raycast_cast(Raycaster*, float, float, float, RaycastColor*);
void            raycast_cast_textured(Raycaster*, float, float, float, RaycastHit*);
RaycastTexture* raycast_texture_create(int, int);
void            raycast_texture_destroy(RaycastTexture*);
void            raycast_add_texture(Raycaster*, RaycastTexture*);
bool            raycast_collides(Raycaster*, float, float);
void            raycast_destroy(Raycaster*);
void            raycast_draw(Raycaster*, const RaycastRect*, const RaycastColor*);
void            raycast_erase(Raycaster*, const RaycastRect*);
Raycaster*      raycast_init(int, int);
int             raycast_init_ptr(Raycaster*, int, int);
void            raycast_move_camera(RaycastCamera*, RaycastDirection, float);
void raycast_move_camera_with_collision(Raycaster*, RaycastCamera*, RaycastDirection, float);
void raycast_render(Raycaster*, const RaycastCamera*, SDL_Renderer*, int, int, const RaycastColor*);
void raycast_render_textured(
    Raycaster*, const RaycastCamera*, SDL_Renderer*, int, int, const RaycastColor*);
void        raycast_render_2d(Raycaster*,
                              const RaycastCamera*,
                              SDL_Renderer*,
                              int,
                              float,
                              const RaycastColor*,
                              const RaycastColor*,
                              const RaycastColor*);
void        raycast_rotate_camera(RaycastCamera*, float);
void        raycast_set_draw_color(SDL_Renderer*, const RaycastColor*);
const char* raycast_version(void);

#endif
