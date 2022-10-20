#include "platform.h"
#include "math.h"
#include "stdio.h"

#define ASPECT_RATIO (16.0f / 9.0f)
#define IMG_WIDTH 960
#define IMG_HEIGHT (u32)(IMG_WIDTH / ASPECT_RATIO)
#define MAX_COLOR_VALUE UINT8_MAX

struct ray {
    point3 orig;
    v3 dir;

    point3 at(r32 t)
    {
        return orig + (t * dir);
    }
};

v3 ray_color(const ray& r) {
    v3 unit_direction = Normalize(r.dir);
    r32 t = 0.5f * (unit_direction.y + 1.0f);
    v3 bg = {1.0f, 1.0f, 1.0f};
    v3 fg = {0.5f, 0.7f, 1.0f};
    return (1.0f - t) * bg + t * fg;
}

void WriteHeader(FILE *f) {
    fprintf(f, "P3\n");
    fprintf(f, "%d ", IMG_WIDTH);
    fprintf(f, "%d \n", IMG_HEIGHT);
    fprintf(f, "%d \n", MAX_COLOR_VALUE);
}

void WritePixelColor(FILE *f, v3 color)
{
    pixel_color pc;
    pc.r = (u8)(color.r * 255.999f);
    pc.g = (u8)(color.g * 255.999f);
    pc.b = (u8)(color.b * 255.999f);

    fprintf(f, "%d %d %d\n", pc.r, pc.g, pc.b);
}

int main() {
    r32 viewport_height = 2.0f;
    r32 viewport_width = viewport_height * ASPECT_RATIO;
    r32 focal_length = 1.0f;

    point3 camera_origin = {0.0f, 0.0f, 0.0f};
    v3 horizontal = {viewport_width, 0.0f, 0.0f};
    v3 vertical = {0.0f, viewport_height, 0.0f};
    v3 depth = {0.0f, 0.0f, focal_length};

    point3 lower_left_corner = camera_origin - (horizontal / 2) - (vertical / 2) - depth;

    char* fileName = "img.ppm";
    FILE *f = fopen(fileName, "wb");

    if (f) 
    {
        WriteHeader(f);

        printf("Raytracing...\n");
        for(s32 j = IMG_HEIGHT - 1;
            j >= 0;
            --j)
        {
            printf("\rScanlines remaining:%d", j);
            for(s32 i = 0;
                i < IMG_WIDTH;
                i++)
            {   
                r32 u = ((r32)i / IMG_WIDTH);
                r32 v = ((r32)j / IMG_HEIGHT);
                ray r = {camera_origin, lower_left_corner + (u * horizontal) + (v * vertical) - camera_origin};
                v3 color = ray_color(r);
                WritePixelColor(f, color);
            }
        }
        printf("\nDone.\n");

        fclose(f);
    } else 
    {
        printf("Could not open file: %s", fileName);
    }

    return 0;
}