#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <string>
#include <iostream>

void keep_green_only(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void channels_swap(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        float temp = color.r;
        color.r = color.b;
        color.b = temp;
    }
}

void black_and_white(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        float luminance = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
        color.r = luminance;
        color.g = luminance;
        color.b = luminance;
    }
}

void negative(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
}

void gradient(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = (1.f / static_cast<float>(image.width())) * x;
            image.pixel(x, y).g = (1.f / static_cast<float>(image.width())) * x;
            image.pixel(x, y).b = (1.f / static_cast<float>(image.width())) * x;
        }
    }
}

void mirror(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 temp_color = image.pixel(x, y);
            image.pixel(x, y) = image.pixel(image.width() - 1 - x, y);
            image.pixel(image.width() - 1 - x, y) = temp_color;
        }
    }
}

void noise(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        if (true_with_probability(0.15))
        {
            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);
        }
    }
}

sil::Image turn_90_deg(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image new_image{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(new_image.width() - 1 - y, x) = image.pixel(x, y);
        }
    }

    return new_image;
}

sil::Image rgb_split(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image new_image{image.width(), image.height()};

    const int gap = 15;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(x, y).r = x >= gap ? image.pixel(x - gap, y).r : 0.f;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(x, y).b = x <= image.width() - 1 - gap ? image.pixel(x + gap, y).r : 0.f;
        }
    }

    return new_image;
}

void lighten(sil::Image &image)
{
    const float power = 0.5;

    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, power);
        color.g = pow(color.g, power);
        color.b = pow(color.b, power);
    }
}

void darken(sil::Image &image)
{
    const float power = 1.5;

    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, power);
        color.g = pow(color.g, power);
        color.b = pow(color.b, power);
    }
}

void disk(sil::Image &image, int centerX, int centerY) // Prend l'image par référence pour pouvoir la modifier
{
    const int radius = 75;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (pow(x - centerX, 2) + pow(y - centerY, 2) < pow(radius, 2))
            {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 0.5;
                image.pixel(x, y).b = 0.7;
            }
        }
    }
}

void circle(sil::Image &image, int centerX, int centerY) // Prend l'image par référence pour pouvoir la modifier
{
    const int radius = 75;
    const int thickness = 4;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow(x - centerX, 2) + pow(y - centerY, 2) < pow(radius, 2)) && (pow(x - centerX, 2) + pow(y - centerY, 2) >= pow(radius - thickness, 2)))
            {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 0.5;
                image.pixel(x, y).b = 0.7;
            }
        }
    }
}

void animation()
{
    const int start = 20;
    for (int i{0}; i < 300; i += 5)
    {
        sil::Image image{300 /*width*/, 300 /*height*/};
        disk(image, start + i, image.height() / 2);
        std::string filepath{"output/gif/" + std::to_string(i) + ".png"};
        image.save(filepath);
    }
}

void rosace(sil::Image &image)
{
    circle(image, image.width() / 2, image.height() / 2);
    for (int i{0}; i < 12; i += 2)
    {
        const double angle = (acos(0.0) / 3) * i;
        int centerX{image.width() / 2 + 75 * cos(angle)};
        int centerY{image.width() / 2 + 75 * sin(angle)};

        centerX = centerX > 150 ? centerX - 1 : centerX + 1;
        centerY = (centerY > 150) && (centerY != 150) ? centerY - 1 : centerY + 1;

        circle(image, centerX, centerY);
    }
}

sil::Image mosaic(sil::Image image, int repetitions)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(x, y) = image.pixel((x * repetitions) % image.width(), (y * repetitions) % image.height());
        }
    }
    return new_image;
}

sil::Image mirrored_mosaic(sil::Image image, int repetitions)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int x_value = (x * repetitions) % image.width();
            int y_value = (y * repetitions) % image.height();

            if (((x * repetitions) / (image.width() - 1)) % 2 == 1)
            {
                x_value = (((image.width() - 1) - x) * repetitions) % image.width();
            }

            if (((y * repetitions) / (image.height() - 1)) % 2 == 1)
            {
                y_value = (((image.height() - 1) - y) * repetitions) % image.height();
            }

            new_image.pixel(x, y) = image.pixel(x_value, y_value);
        }
    }
    return new_image;
}

void white_noise_map(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float brightness = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
        float random_value = random_float(0.f, 1.f);

        if (brightness > random_value)
        {
            color.r = 1.f;
            color.g = 1.f;
            color.b = 1.f;
        }
        else
        {
            color.r = 0.f;
            color.g = 0.f;
            color.b = 0.f;
        }
    }
}

void bayer_map(sil::Image &image)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {-0.5, 0, -0.375, 0.125},
        {0.25, -0.25, 0.375, -0.125},
        {-0.3125, 0.1875, -0.4375, 0.0625},
        {0.4375, -0.0625, 0.3125, -0.1875},
    };

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 &color = image.pixel(x, y);
            float brightness = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
            const float output_color = brightness + (bayer_matrix_4x4[x % bayer_n][y % bayer_n]);

            if (output_color > 0.5)
            {
                color.r = 1.f;
                color.g = 1.f;
                color.b = 1.f;
            }
            else
            {
                color.r = 0.f;
                color.g = 0.f;
                color.b = 0.f;
            }
        }
    }
}

void dither(sil::Image &image, std::string map)
{
    if (map == "bayer")
    {
        bayer_map(image);
    }

    if (map == "white noise")
    {
        white_noise_map(image);
    }
}

void convolution(sil::Image &image, std::vector<std::vector<float>> &kernel)
{
    sil::Image const original = image;
    int radius = kernel.size()/2.f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 sum{0.f};

            for (int kx{0}; kx < kernel.size(); kx++)
            {
                for (int ky{0}; ky < kernel.size(); ky++)
                {
                    int const neighbor_x = std::max(0, std::min(x + kx - radius, image.width() - 1));
                    int const neighbor_y = std::max(0, std::min(y + ky - radius, image.height() - 1));

                    sum += kernel[kx][ky] * original.pixel(neighbor_x,neighbor_y);
                }
            }

            image.pixel(x,y) = sum;
        }
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};      // Lis l'image
        keep_green_only(image);                   // Utilise la fonction pour modifier l'image
        image.save("output/keep_green_only.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        channels_swap(image); // Utilise la fonction pour modifier l'image
        image.save("output/channels_swap.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"};
        black_and_white(image);
        image.save("output/black_and_white.png");
    }
    {
        sil::Image image{"images/logo.png"};
        negative(image);
        image.save("output/negative.png");
    }
    {
        sil::Image image{300 /*width*/, 200 /*height*/};
        gradient(image);
        image.save("output/gradient.png");
    }
    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }
    {
        sil::Image image{"images/logo.png"};
        noise(image);
        image.save("output/noise.png");
    }
    {
        sil::Image image{"images/logo.png"};
        turn_90_deg(image).save("output/90deg.png");
    }
    {
        sil::Image image{"images/logo.png"};
        rgb_split(image).save("output/rgb_split.png");
    }
    {
        sil::Image image{"images/photo.jpg"};
        lighten(image);
        image.save("output/lighten.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        darken(image);
        image.save("output/darken.jpg");
    }
    {
        sil::Image image{300 /*width*/, 300 /*height*/};
        disk(image, image.width() / 2, image.height() / 2);
        image.save("output/disk.png");
    }
    {
        sil::Image image{300 /*width*/, 300 /*height*/};
        circle(image, image.width() / 2, image.height() / 2);
        image.save("output/circle.png");
    }
    {
        animation();
    }
    {
        sil::Image image{300 /*width*/, 300 /*height*/};
        rosace(image);
        image.save("output/rosace.png");
    }
    {
        sil::Image image{"images/logo.png"};
        mosaic(image, 5).save("output/mosaic.png");
    }
    {
        sil::Image image{"images/logo.png"};
        mirrored_mosaic(image, 5).save("output/mirrored_mosaic.png");
    }
    {
        sil::Image image{"images/photo.jpg"};
        dither(image, "bayer");
        image.save("output/dither.jpg");
    }
    {
        sil::Image image{"images/photo.jpg"};
        dither(image, "white noise");
        image.save("output/white_noise.jpg");
    }
    {
        std::vector<std::vector<float>> box_blur_kernel =
        {{1.f/9.f,1.f/9.f,1.f/9.f},
        {1.f/9.f,1.f/9.f,1.f/9.f},
        {1.f/9.f,1.f/9.f,1.f/9.f}};

        std::vector<std::vector<float>> emboss_kernel =
        {{-2.f,-1.f,0.f},
        {-1.f,1.f,1.f},
        {0.f,1.f,2.f}};

        std::vector<std::vector<float>> outline_kernel =
        {{-1.f,-1.f,-1.f},
        {-1.f,8.f,-1.f},
        {-1.f,-1.f,-1.f}};

        std::vector<std::vector<float>> sharpen_kernel =
        {{0.f,-1.f,0.f},
        {-1.f,5.f,-1.f},
        {0.f,-1.f,0.f}};

        sil::Image image{"images/logo.png"};
        convolution(image, box_blur_kernel);
        image.save("output/convolution_box_blur.png");

        sil::Image image2{"images/logo.png"};
        convolution(image2, emboss_kernel);
        image2.save("output/convolution_emboss.png");

        sil::Image image3{"images/logo.png"};
        convolution(image3, outline_kernel);
        image3.save("output/convolution_outline.png");

        sil::Image image4{"images/logo.png"};
        convolution(image4, sharpen_kernel);
        image4.save("output/convolution_sharpen.png");
    }
}