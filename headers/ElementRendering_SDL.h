#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

using namespace std;

namespace ElementRendering_SDL
{
    /*
    ## Função: ButtonText / Function: ButtonText

    Esta função é responsável por criar um botão na tela utilizando SDL. O botão é composto por um texto centralizado sobre um fundo colorido.
    Ela desenha o botão no local especificado com as dimensões e cores fornecidas.

    This function is responsible for creating a button on the screen using SDL. The button consists of centered text over a colored background.
    It renders the button at the specified location with the given dimensions and colors.

    ### Parâmetros / Parameters:
    - `renderer`: O renderizador SDL onde o botão será desenhado. / The SDL renderer where the button will be drawn.
    - `rectX`: A coordenada X da posição do botão. / The X coordinate of the button's position.
    - `rectY`: A coordenada Y da posição do botão. / The Y coordinate of the button's position.
    - `rectWidth`: A largura do botão em pixels. / The width of the button in pixels.
    - `rectHeight`: A altura do botão em pixels. / The height of the button in pixels.
    - `text`: O texto a ser exibido no botão. / The text to be displayed on the button.
    - `fontSize`: O tamanho da fonte do texto. / The font size for the text.
    - `fontColor`: A cor do texto, representada por `SDL_Color`. / The color of the text, represented by `SDL_Color`.
    - `bgColor`: A cor de fundo do botão, representada como um vetor de 4 elementos (R, G, B, A), onde cada valor varia de 0 a 255.
      / The background color of the button, represented as a vector of 4 elements (R, G, B, A), where each value ranges from 0 to 255.
    - `fontPath`: O caminho para o arquivo de fonte a ser utilizado. / The path to the font file to be used.

    ### Funcionamento / Functioning:
    1. A função carrega a fonte do caminho especificado. / The function loads the font from the specified path.
    2. Cria uma superfície contendo o texto. / It creates a surface containing the text.
    3. Converte a superfície em uma textura. / It converts the surface into a texture.
    4. Desenha um retângulo de fundo com a cor especificada e as dimensões fornecidas. / It draws a background rectangle with the specified color and dimensions.
    5. Centraliza e renderiza o texto dentro do botão. / It centers and renders the text within the button.

    ### Exemplo de uso / Example of use:
    ButtonText(renderer, 0, 0, 100, 32, "TESTE", 14, {255, 255, 255, 255}, {0, 0, 0, 255}, "assets/fonts/Roboto-Bold.ttf");

    ### Retorno:
    0: criado com sucesso.
    -1: Fonte não encontrada.
    -2: Surface não criada.
    -3: Textura não criada.
    -4: QueryTexture falhou.
    */
    int ButtonText(SDL_Renderer *renderer, int rectX, int rectY, int rectWidth, int rectHeight, const char *text, int fontSize, SDL_Color fontColor, vector<int> bgColor, const char *fontPath)
    {
        int larguraFonte, alturaFonte;
        TTF_Font *fontMenu = TTF_OpenFont(fontPath, fontSize);
        if (!fontMenu)
        {
            cout << "Fonte não existe dentro da pasta assets/fontes/" << endl;
            return -1;
        }
        SDL_Surface *fontSurface = TTF_RenderText_Blended(fontMenu, text, fontColor);
        if (!fontSurface)
        {
            cout << "Verifique a cor da fonte, ou o texto inserido. Não foi possivel carregar." << endl;
            TTF_CloseFont(fontMenu);
            return -2;
        }
        SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
        if (!fontTexture)
        {
            cout << "Não foi possivel criar uma superficie com o texto escolhido." << endl;
            TTF_CloseFont(fontMenu);
            SDL_FreeSurface(fontSurface);
            return -3;
        }
        if (SDL_QueryTexture(fontTexture, nullptr, nullptr, &larguraFonte, &alturaFonte) != 0)
        {
            cout << "Não foi possivel capturar os dados da textura da fonte, tais como, largura, altura..." << endl;
            TTF_CloseFont(fontMenu);
            SDL_FreeSurface(fontSurface);
            SDL_DestroyTexture(fontTexture);
            return -4;
        }

        SDL_Rect fontRect = {rectX + rectWidth / 2 - larguraFonte / 2, rectY + rectHeight / 2 - alturaFonte / 2, larguraFonte, alturaFonte};
        SDL_SetRenderDrawColor(renderer, bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        SDL_Rect fontRectBack = {rectX, rectY, rectWidth, rectHeight};
        SDL_RenderFillRect(renderer, &fontRectBack);
        SDL_RenderCopy(renderer, fontTexture, nullptr, &fontRect);
        return 0;
    }

    /*
    ## Função: ButtonIcon / Function: ButtonIcon

    Esta função desenha um botão na tela com um ícone centralizado. O botão possui um fundo colorido e um ícone carregado de um arquivo de imagem.

    This function renders a button on the screen with a centered icon. The button has a colored background and an icon loaded from an image file.

    ### Parâmetros / Parameters:
    - `renderer`: O renderizador SDL onde o botão será desenhado. / The SDL renderer where the button will be drawn.
    - `rectX`: A coordenada X da posição do botão. / The X coordinate of the button's position.
    - `rectY`: A coordenada Y da posição do botão. / The Y coordinate of the button's position.
    - `rectWidth`: A largura do botão em pixels. / The width of the button in pixels.
    - `rectHeight`: A altura do botão em pixels. / The height of the button in pixels.
    - `iconPath`: O caminho para o arquivo de imagem que contém o ícone. / The path to the image file containing the icon.
    - `bgColor`: A cor de fundo do botão, representada como um vetor de 4 elementos (R, G, B, A), onde cada valor varia de 0 a 255.
    / The background color of the button, represented as a vector of 4 elements (R, G, B, A), where each value ranges from 0 to 255.

    ### Funcionamento / Functioning:
    1. A função carrega o ícone a partir do arquivo de imagem especificado em `iconPath`.
    / The function loads the icon from the image file specified in `iconPath`.
    2. Define a opacidade total para a superfície do ícone. / Sets full opacity for the icon surface.
    3. Converte a superfície em uma textura para renderização. / Converts the surface into a texture for rendering.
    4. Desenha um retângulo de fundo com as dimensões e cor especificadas. / Draws a background rectangle with the specified dimensions and color.
    5. Centraliza e renderiza o ícone dentro do botão. / Centers and renders the icon within the button.

    ### Exemplo de uso / Example of use:
    ButtonIcon(renderer, 0, 0, 100, 32, "assets/icons/close.png", {0, 0, 0, 255});
    */
    int ButtonIcon(SDL_Renderer *renderer, int rectX, int rectY, int rectWidth, int rectHeight, const char *iconPath, vector<int> bgColor)
    {
        int larguraFonte, alturaFonte;
        SDL_Surface *surface = IMG_Load(iconPath);
        SDL_SetSurfaceAlphaMod(surface, SDL_ALPHA_OPAQUE);
        SDL_Texture *icon = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect iconRect = {rectX, rectY, surface->w, surface->h};
        cout << surface->w << endl;
        SDL_Rect bgRect = {rectX, rectY, 30, 30};

        SDL_SetRenderDrawColor(renderer, bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        SDL_RenderFillRect(renderer, &bgRect);

        SDL_RenderCopy(renderer, icon, nullptr, &iconRect);
        return 0;
    }
    /*
    ## Função: Text / Function: Text

    Esta função é responsável por renderizar texto na tela usando SDL e SDL_ttf. Ela carrega uma fonte, cria uma superfície de texto renderizada, converte essa superfície em textura e a desenha na posição especificada.

    This function is responsible for rendering text on the screen using SDL and SDL_ttf. It loads a font, creates a rendered text surface, converts this surface into a texture, and draws it at the specified position.

    ### Parâmetros / Parameters:
    - `renderer`: O renderizador SDL onde o texto será desenhado. / The SDL renderer where the text will be drawn.
    - `fontPath`: O caminho para o arquivo de fonte (TTF). / The path to the font file (TTF).
    - `fontSize`: O tamanho da fonte a ser utilizada. / The font size to be used.
    - `fontColor`: A cor do texto, representada como uma estrutura `SDL_Color` (R, G, B, A). 
    / The color of the text, represented as an `SDL_Color` structure (R, G, B, A).
    - `text`: O texto a ser exibido. / The text to be displayed.
    - `fontX`: A coordenada X onde o texto será desenhado. / The X coordinate where the text will be drawn.
    - `fontY`: A coordenada Y onde o texto será desenhado. / The Y coordinate where the text will be drawn.

    ### Funcionamento / Functioning:
    1. A função tenta abrir a fonte especificada pelo caminho e tamanho fornecidos. 
    / The function attempts to open the font specified by the provided path and size.
    2. Cria uma superfície com o texto renderizado na cor fornecida. 
    / It creates a surface with the rendered text in the provided color.
    3. Converte a superfície de texto em uma textura SDL para renderização. 
    / It converts the text surface into an SDL texture for rendering.
    4. Obtém as dimensões do texto renderizado (largura e altura). 
    / It retrieves the dimensions of the rendered text (width and height).
    5. Desenha a textura na posição especificada. 
    / It draws the texture at the specified position.
    Text(renderer, "assets/fonts/Roboto-Bold.ttf", 14, {255, 255, 255, 255}, "Text here!", 0, 0);
    */
    void Text(SDL_Renderer *renderer, const char *fontPath, int fontSize, SDL_Color fontColor, const char *text, int fontX, int fontY)
    {
        TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
        if (!font)
        {
            cout << "Fonte não existe." << endl;
            return;
        }
        SDL_Surface *surface = TTF_RenderText_Blended(font, text, fontColor);
        if (surface == NULL)
        {
            TTF_CloseFont(font);
            cout << "Superfice para fonte não foi criada, verifique o texto inserido ou a cor." << endl;
            return;
        }
        SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (fontTexture == NULL)
        {
            TTF_CloseFont(font);
            SDL_FreeSurface(surface);
            cout << "Textura não foi criada, verifique se o renderer " << endl;
            return;
        }
        int fontW, fontH;
        SDL_QueryTexture(fontTexture, nullptr, nullptr, &fontW, &fontH);
        SDL_Rect fontRect = {fontX, fontY, fontW, fontH};
        SDL_RenderCopy(renderer, fontTexture, nullptr, &fontRect);
    }
}