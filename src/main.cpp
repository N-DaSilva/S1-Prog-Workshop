#include <sil/sil.hpp>

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
}