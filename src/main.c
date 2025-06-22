#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "main.h"


SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
SDL_Surface *surface_background =NULL;
SDL_Texture *texture_background =NULL;
SDL_Surface *surface_backgroundp =NULL;
SDL_Texture *texture_backgroundp =NULL;
SDL_Surface *surface_people =NULL;
SDL_Texture *texture_people =NULL;
SDL_Rect rect_people;
SDL_Surface *surface_backgroundc =NULL;
SDL_Texture *texture_backgroundc =NULL;
SDL_Surface *surface_pingtai1 =NULL;
SDL_Texture *texture_pingtai1 =NULL;
SDL_Rect rect_pingtai1;
SDL_Surface *surface_pingtai2 =NULL;
SDL_Texture *texture_pingtai2 =NULL;
SDL_Rect rect_pingtai2;
SDL_Surface *surface_pingtai3 =NULL;
SDL_Texture *texture_pingtai3 =NULL;
SDL_Rect rect_pingtai3;
TTF_Font *font_score=NULL;
TTF_Font *font_bests=NULL;
SDL_Surface *surface_score =NULL;
SDL_Texture *texture_score =NULL;
SDL_Rect rect_score;
TTF_Font *font_bests1=NULL;
SDL_Surface *surface_score1 =NULL;
SDL_Texture *texture_score1 =NULL;
SDL_Rect rect_score1;
TTF_Font *font_score1=NULL;
SDL_Surface *surface_bests1 =NULL;
SDL_Texture *texture_bests1 =NULL;
SDL_Rect rect_bests1;
SDL_Surface *surface_bests =NULL;
SDL_Texture *texture_bests =NULL;
SDL_Rect rect_bests;
TTF_Font *font_score2=NULL;
SDL_Surface *surface_score2 =NULL;
SDL_Texture *texture_score2 =NULL;
SDL_Rect rect_score2;
SDL_Color FontColor={255,255,255,255};
SDL_Surface *surface_rule =NULL;
SDL_Texture *texture_rule=NULL;
TTF_Font *font_zuan=NULL;
SDL_Surface *surface_zuan =NULL;
SDL_Texture *texture_zuan =NULL;
SDL_Rect rect_zuan;

Mix_Chunk *xulim =NULL;
Mix_Music *bgm=NULL;
Mix_Chunk *tiaoyuem =NULL;
Mix_Chunk *shibai =NULL;
Mix_Chunk *doubles =NULL;




int game0=0;//判断是否在游戏中，0时是主界面或end界面，1时是蓄力状态，2时是跳跃状态
int xp=0;//人物的横坐标
int jiafen0=0;//每个物块对应的加分
int blockw=200;//物块宽度
int num=1;//方块个数
int best=0;//最高得分
int zuanshishu;//钻石数量
char zuanshis[10]={0};
char b[1000]={0};
char score0[1000]={0};//下一个方块加的分
char b1[1000]={0};
char score1[1000]={0};
char jia[10]={0};
int zongfen=0;//游戏得分
int music =0;
int isFiring=0;//空格是否按下，是为1，否为0
float power=0;
//物块数组
typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
}block;
//物块种类数组
typedef struct{
    SDL_Rect rect;
    SDL_Texture *texture;
}blockstyle;
block blocks[1700];
blockstyle styles[3];
int rules=0;


#undef main
int main() {
//初始化
    init_app();
//载入图像
    load();
//显示主界面
    draw_begin();
    game0 = 0;
    fangbgm();
//主循环事件
    while (1) {
        SDL_Event event;
        //键盘蓄力事件，要有蓄力状态，蓄力有上限，跳跃时不可以蓄力
        if (isFiring == 1 && game0 == 1)
        {
            xuli();
        }

        while (SDL_PollEvent(&event)) {


            switch (event.type) {
                case SDL_QUIT:
                    quit_app();

                    return 0;
                case SDL_MOUSEBUTTONDOWN://鼠标按下
                    printf("button  at (%d,%d)\n", event.button.x, event.button.y);//记录鼠标按下时坐标
                    if (event.button.x >= 567 && event.button.x <= 934 && event.button.y >= 423 &&
                        event.button.y <= 538 && game0 == 0) {
                        printf("begin!");
                        game0 = 1;
                        if(rules==0)
                        {
                            game0=7;
                            ruless();
                            break;
                        }
                        game();//进入游戏
                        jiafen0 = play();//产生一个随机平台
                        break;

                    } else if (event.button.x >= 549 && event.button.x <= 944 && event.button.y >= 592 &&
                               event.button.y <= 705) {
                        quit_app();

                        return 0;
                    }
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE && game0 == 1) {
                        isFiring = 1;
                        if(music==0) {
                            xulimu();
                        }
                        break;

                    }
                    else if(event.key.keysym.sym ==  SDLK_1 && game0 == 7)
                    {
                        game0=1;
                        game();//进入游戏
                        jiafen0 = play();//产生一个随机平台
                        break;
                    }
                    else if(event.key.keysym.sym ==  SDLK_7 && game0 == 1&&zuanshishu>0)
                    {
                        game0=2;
                        zuanshishu--;
                        tiaoyuemu();
                        power=(rect_people.x-blocks[num-1].rect.x-17)/2080.0;
                        xp=jump();
                        rect_people.h=80;
                        rect_people.y=460;
                        if(jiafen0==2)
                        {
                            zuanshishu++;
                        }
                        draw_game();
                        doublesmu();
                        zongfen=zongfen+jiafen0;

                        if(zongfen>best)
                        {
                            best=zongfen;
                        }
                        printjia();
                        pingyi();
                        jiafen0 =play();
                        power=0;
                        game0=1;
                        break;

                    }
                    else if(event.key.keysym.sym ==  SDLK_0 && game0 == 1)
                    {
                        game0=2;
                        tiaoyuemu();
                        power=(rect_people.x-blocks[num-1].rect.x-17)/2080.0;
                        xp=jump();
                        rect_people.h=80;
                        rect_people.y=460;
                        if(jiafen0==2)
                        {
                            zuanshishu++;
                        }
                        draw_game();
                        doublesmu();
                        zongfen=zongfen+jiafen0;

                        if(zongfen>best)
                        {
                            best=zongfen;
                        }
                        printjia();
                        pingyi();
                        jiafen0 =play();
                        power=0;
                        game0=1;
                        break;

                    }

                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_SPACE && game0 == 1) {
                        isFiring = 0;
                        Mix_HaltChannel(1);
                        music=0;
                        tiaoyuemu();
                        game0 = 2;
                        //跳跃函数，实现跳跃动画，返回最终x坐标
                        xp = jump();

                        //判断x是否在范围内
                        int pp = panduan();
                        //若在上一个则返回蓄力
                        if(pp==-1)
                        {
                            game0=1;
                            rect_people.h=80;
                            rect_people.y=460;
                            draw_game();
                            power=0;
                           break;
                        }

                        // 若在下一个则执行加分动画，加分数，判断替换最高分,平移，产生新平台
                        if(pp==0)
                        {
                            rect_people.h=80;
                            rect_people.y=460;
                            if(jiafen0==2)
                            {
                                zuanshishu++;
                            }
                            draw_game();
                            doublesmu();
                            zongfen=zongfen+jiafen0;

                            if(zongfen>best)
                            {
                                best=zongfen;
                            }
                            printjia();
                            pingyi();
                            jiafen0 =play();
                            power=0;
                            game0=1;
                            break;
                        }

                        //若不在则弹出end界面，弹出分数和最高分
                        if(pp==1)
                        {

                            power=0;
                            shibaimu();
                            rect_people.h=80;
                            rect_people.y=460;
                            luoxia();
                            end();
                            break;

                        }

                        break;

                    }

                default:
                    break;
            }
        }
            //每十六毫秒刷新
        SDL_RenderPresent(renderer);
            SDL_Delay(16);

    }

}


static void ruless()//加载规则界面
{
    rules=1;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_rule, NULL, NULL);
    SDL_RenderPresent(renderer);

}

static void luoxia()
{
    while(rect_people.y<580)
    {
        rect_people.y++;
        draw_game();

    }
}

static void xulimu()
{
music=1;
    //Mix_Volume(1,100);
    Mix_PlayChannel(1,xulim,0);


}
static void fangbgm()
{ Mix_VolumeMusic(3);
    Mix_PlayMusic(bgm,-1);
}

static void tiaoyuemu()

{

    Mix_PlayChannel(2,tiaoyuem,0);
}
static void shibaimu()
{
    Mix_Volume(3,100);
    Mix_PlayChannel(3,shibai,0);

}
static void doublesmu()
{
    Mix_PlayChannel(4,doubles,0);

}

static void printjia()
{
    if(jiafen0<0) {
        sprintf(jia, "%d", jiafen0);
    }
    else

    {
        sprintf(jia, "+%d", jiafen0);
    }


    surface_score2= TTF_RenderUTF8_Blended(font_score2,jia,FontColor);
    texture_score2= SDL_CreateTextureFromSurface(renderer,surface_score2);
    rect_score2.x=rect_people.x+15;
    rect_score2.y=430;
    SDL_QueryTexture(texture_score2,NULL,NULL,&rect_score2.w,&rect_score2.h);
    SDL_RenderCopy(renderer,texture_score2,NULL,&rect_score2);


    SDL_RenderPresent(renderer);
    SDL_Delay(500);
}

static int play()//产生随机平台
{
    //随机产生一个平台，不同平台代号x不同，记得平台缩小，距离也随机但有范围，记录平台坐标
    styles[0].texture= SDL_CreateTextureFromSurface(renderer,surface_pingtai3);
    styles[1].texture= SDL_CreateTextureFromSurface(renderer,surface_pingtai2);
    styles[2].texture= SDL_CreateTextureFromSurface(renderer,surface_pingtai1);
    int randomstyle=rand()%10;
if(randomstyle<6)
{
    randomstyle=0;
}
else if(randomstyle>5&&randomstyle<9)
{
    randomstyle=1;
}
else
{
    randomstyle=2;
}
    int randomx=rand();

    while(randomx<200||randomx>800)
    {
        randomx=rand();
    }


    blocks[num].rect.x=randomx;
    blocks[num].rect.y=520;
    blocks[num].rect.w=blockw;
    blocks[num].rect.h=140;


    if(blockw>80)
    {
        blockw=blockw-5;
    }

    blocks[num].texture=styles[randomstyle].texture;

    num++;

    int jiafen=randomstyle;
    if(jiafen==0)
    {
        jiafen=1;
    }
    else if(jiafen==1)
    {
        jiafen =2;

    }
    else
    {
        int m=rand()%8;
        if(m<6)
        {
            jiafen=-3;
        }
        else
        {
            jiafen=3;
        }
        //随机3和-3

    }
    SDL_RenderCopy(renderer, blocks[num-1].texture, NULL, &blocks[num-1].rect);
    SDL_RenderPresent(renderer);



    return jiafen;
}
static void load()//加载
{
    xulim= Mix_LoadWAV("src/xxxuli.mp3");
    if(xulim==NULL)
    {
        printf("shibaile\n");
    }
    bgm= Mix_LoadMUS("src/bgm.mp3");
    tiaoyuem= Mix_LoadWAV("src/tiaoyue.mp3");
    shibai= Mix_LoadWAV("src/shibai.mp3");
    doubles= Mix_LoadWAV("src/doubles.mp3");

    surface_rule = IMG_Load("src/rule3.png");
    texture_rule = SDL_CreateTextureFromSurface(renderer, surface_rule);



    surface_background = IMG_Load("src/begin.jpg");
    texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);


    surface_backgroundp = IMG_Load("src/beijing.png");
    texture_backgroundp = SDL_CreateTextureFromSurface(renderer, surface_backgroundp);

    font_score = TTF_OpenFont("src/ziti.ttf",50);
    if(font_score==NULL)
    {
        printf("can not font");
        return;
    }
    sprintf(score0, "分数 : %d", zongfen);


    surface_score= TTF_RenderUTF8_Blended(font_score,score0,FontColor);
    texture_score= SDL_CreateTextureFromSurface(renderer,surface_score);
    rect_score.x=14;
    rect_score.y=30;
    SDL_QueryTexture(texture_score,NULL,NULL,&rect_score.w,&rect_score.h);

    font_bests = TTF_OpenFont("src/ziti.ttf",50);
    if(font_bests==NULL)
    {
        printf("can not font");
        return;
    }
    sprintf(b, "最高得分 : %d", best);
    surface_bests= TTF_RenderUTF8_Blended(font_bests,b,FontColor);
    texture_bests= SDL_CreateTextureFromSurface(renderer,surface_bests);
    rect_bests.x=14;
    rect_bests.y=80;
    SDL_QueryTexture(texture_bests,NULL,NULL,&rect_bests.w,&rect_bests.h);



    font_score1 = TTF_OpenFont("src/ziti.ttf",70);
    if(font_score==NULL)
    {
        printf("can not font");
        return;
    }
    sprintf(score1, "%d", zongfen);

    surface_score1= TTF_RenderUTF8_Blended(font_score1,score1,FontColor);
    texture_score1= SDL_CreateTextureFromSurface(renderer,surface_score1);
    rect_score1.x=806;
    rect_score1.y=107;
    SDL_QueryTexture(texture_score1,NULL,NULL,&rect_score1.w,&rect_score1.h);

    font_zuan = TTF_OpenFont("src/ziti.ttf",50);
    if(font_zuan==NULL)
    {
        printf("can not font zuan");
        return;
    }
    sprintf(zuanshis, "%d", zuanshishu);
    surface_zuan= TTF_RenderUTF8_Blended(font_zuan,zuanshis,FontColor);
    texture_zuan= SDL_CreateTextureFromSurface(renderer,surface_zuan);
    rect_zuan.x=1265;
    rect_zuan.y=18;
    SDL_QueryTexture(texture_zuan,NULL,NULL,&rect_zuan.w,&rect_zuan.h);


    font_bests1 = TTF_OpenFont("src/ziti.ttf",70);
    if(font_bests==NULL)
    {
        printf("can not font");
        return;
    }
    sprintf(b1, "%d", best);
    surface_bests1= TTF_RenderUTF8_Blended(font_bests1,b1,FontColor);
    texture_bests1= SDL_CreateTextureFromSurface(renderer,surface_bests1);
    rect_bests1.x=806;
    rect_bests1.y=195;
    SDL_QueryTexture(texture_bests1,NULL,NULL,&rect_bests1.w,&rect_bests1.h);

    font_score2 = TTF_OpenFont("src/ziti.ttf",25);
    if(font_score2==NULL)
    {
        printf("can not font");
        return;
    }
    sprintf(jia, "%d", jiafen0);


    surface_score2= TTF_RenderUTF8_Blended(font_score2,jia,FontColor);
    texture_score2= SDL_CreateTextureFromSurface(renderer,surface_score2);
    rect_score2.x=14;
    rect_score2.y=30;
    SDL_QueryTexture(texture_score2,NULL,NULL,&rect_score2.w,&rect_score2.h);




    surface_people = IMG_Load("src/people1.png");
    rect_people.x=1240;
    rect_people.y=460;
    rect_people.w=70;
    rect_people.h=80;
    texture_people = SDL_CreateTextureFromSurface(renderer, surface_people);

    surface_backgroundc = IMG_Load("src/end1.jpg");
    texture_backgroundc = SDL_CreateTextureFromSurface(renderer, surface_backgroundc);

    surface_pingtai1 = IMG_Load("src/mogu.png");
    texture_pingtai1 = SDL_CreateTextureFromSurface(renderer, surface_pingtai1);
    rect_pingtai1.x=1200;
    rect_pingtai1.y=520;
    rect_pingtai1.w=200;
    rect_pingtai1.h=140;

    surface_pingtai2 = IMG_Load("src/cao.png");
    texture_pingtai2 = SDL_CreateTextureFromSurface(renderer, surface_pingtai2);
    rect_pingtai2.x=1200;
    rect_pingtai2.y=520;
    rect_pingtai2.w=200;
    rect_pingtai2.h=140;


    rect_pingtai3.x=1200;
    rect_pingtai3.y=520;
    rect_pingtai3.w=200;
    rect_pingtai3.h=140;
    surface_pingtai3 = IMG_Load("src/mu.png");
    texture_pingtai3 = SDL_CreateTextureFromSurface(renderer, surface_pingtai3);

    blocks[0].texture=texture_pingtai3;
    blocks[0].rect= rect_pingtai3;

}
static void init_app()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0)
    {
        printf("Init SDL:%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)){
        printf("Init SDL:%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(!Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG))
    {
        printf("Init SDL:%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init()==-1)
    {
        printf("Init SDL:%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Init();

// 创建窗口
    window = SDL_CreateWindow("jump!", 100, 100, 1400, 800, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return ;
    }

// 初始化渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return ;
    }
    //音乐初始化
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
}
static void quit_app()
{
    SDL_FreeSurface(surface_backgroundp);
    SDL_FreeSurface(surface_score);
    SDL_FreeSurface(surface_people);
    SDL_FreeSurface(surface_backgroundc);
    SDL_FreeSurface(surface_pingtai1);
    SDL_FreeSurface(surface_pingtai2);
    SDL_FreeSurface(surface_pingtai3);
    SDL_FreeSurface(surface_background);
    SDL_FreeSurface(surface_bests);
    SDL_FreeSurface(surface_bests1);
    SDL_FreeSurface(surface_score1);
    SDL_FreeSurface(surface_zuan);
    SDL_FreeSurface(surface_score2);
    SDL_FreeSurface(surface_rule);
    Mix_FreeChunk(xulim);
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(tiaoyuem);
    Mix_FreeChunk(shibai);
    Mix_FreeChunk(doubles);




    SDL_DestroyTexture(texture_background);
    SDL_DestroyTexture(texture_backgroundp);
    SDL_DestroyTexture(texture_score);
    SDL_DestroyTexture(texture_bests);
    SDL_DestroyTexture(texture_people);
    SDL_DestroyTexture(texture_backgroundc);
    SDL_DestroyTexture(texture_pingtai1);
    SDL_DestroyTexture(texture_pingtai2);
    SDL_DestroyTexture(texture_pingtai3);
    SDL_DestroyTexture(texture_score1);
    SDL_DestroyTexture(texture_bests1);
    SDL_DestroyTexture(texture_score2);
    SDL_DestroyTexture(texture_rule);
    SDL_DestroyTexture(texture_zuan);

    TTF_CloseFont(font_score);
    TTF_CloseFont(font_bests);
    TTF_CloseFont(font_score1);
    TTF_CloseFont(font_bests1);
    TTF_CloseFont(font_score2);
    TTF_CloseFont(font_zuan);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();


}
static void game()//加载游戏初始界面
{
    //加载游戏界面
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_backgroundp, NULL, NULL);
    //加载人物和初始平台
    SDL_RenderCopy(renderer, blocks[0].texture, NULL, &blocks[0].rect);
    SDL_RenderCopy(renderer, texture_people, NULL, &rect_people);
    //加载文字
    sprintf(score0, "分数 : %d", zongfen);
    sprintf(b, "最高得分 : %d", best);
    sprintf(zuanshis, "%d", zuanshishu);

    surface_score= TTF_RenderUTF8_Blended(font_score,score0,FontColor);
    texture_score= SDL_CreateTextureFromSurface(renderer,surface_score);
    SDL_QueryTexture(texture_score,NULL,NULL,&rect_score.w,&rect_score.h);
    SDL_RenderCopy(renderer,texture_score,NULL,&rect_score);

    surface_bests= TTF_RenderUTF8_Blended(font_bests,b,FontColor);
    texture_bests= SDL_CreateTextureFromSurface(renderer,surface_bests);
    SDL_QueryTexture(texture_bests,NULL,NULL,&rect_bests.w,&rect_bests.h);
    SDL_RenderCopy(renderer,texture_bests,NULL,&rect_bests);

    surface_zuan= TTF_RenderUTF8_Blended(font_zuan,zuanshis,FontColor);
    texture_zuan= SDL_CreateTextureFromSurface(renderer,surface_zuan);
    SDL_QueryTexture(texture_zuan,NULL,NULL,&rect_zuan.w,&rect_zuan.h);
    SDL_RenderCopy(renderer,texture_zuan,NULL,&rect_zuan);

    SDL_RenderPresent(renderer);
    return;
}

static void draw_begin()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_background, NULL, NULL);
    SDL_RenderPresent(renderer);

}
static void draw_end()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_backgroundc, NULL, NULL);
    //打印得分和最高分



    SDL_RenderPresent(renderer);

}
static void draw_game()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_backgroundp, NULL, NULL);
    SDL_RenderCopy(renderer, blocks[num-1].texture, NULL, &blocks[num-1].rect);
    SDL_RenderCopy(renderer, blocks[num-2].texture, NULL, &blocks[num-2].rect);
    SDL_RenderCopy(renderer, texture_people, NULL, &rect_people);
    sprintf(score0, "分数 : %d", zongfen);
    sprintf(b, "最高得分 : %d", best);
    sprintf(zuanshis, "%d", zuanshishu);

    surface_score= TTF_RenderUTF8_Blended(font_score,score0,FontColor);
    texture_score= SDL_CreateTextureFromSurface(renderer,surface_score);
    SDL_QueryTexture(texture_score,NULL,NULL,&rect_score.w,&rect_score.h);
    SDL_RenderCopy(renderer,texture_score,NULL,&rect_score);

    surface_zuan= TTF_RenderUTF8_Blended(font_zuan,zuanshis,FontColor);
    texture_zuan= SDL_CreateTextureFromSurface(renderer,surface_zuan);
    SDL_QueryTexture(texture_zuan,NULL,NULL,&rect_zuan.w,&rect_zuan.h);
    SDL_RenderCopy(renderer,texture_zuan,NULL,&rect_zuan);

    surface_bests= TTF_RenderUTF8_Blended(font_bests,b,FontColor);
    texture_bests= SDL_CreateTextureFromSurface(renderer,surface_bests);
    SDL_QueryTexture(texture_bests,NULL,NULL,&rect_bests.w,&rect_bests.h);
    SDL_RenderCopy(renderer,texture_bests,NULL,&rect_bests);


    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}
static void xuli()//蓄力，要有蓄力状态，返回蓄力结果，蓄力有上限，跳跃时不可以蓄力
{
    power=power+0.01f;
    rect_people.h=80-power*80.0f;

    if(rect_people.h<40)
    {
        rect_people.h=40;
    }
    rect_people.y=rect_pingtai1.y-rect_people.h+20;
    if(power>=0.5)
    {
        power=0.5;

    }
    draw_game();

    return ;

}
static int jump()//跳跃
{
    rect_people.h=80;
    rect_people.y=460;
    float a = 0.0;
    int dx=0;
    float dy=18.72;
    float dyy=18.72;
    for ( dx = 0; dx <= (power*104); dx++) {
        a=dyy/(power*104);
        rect_people.x= rect_people.x-10;
        dy=dy-a;
        rect_people.y= rect_people.y-dy;
        draw_game();
    }
    for ( dx =(power*104); dx <= (power*208); dx++) {

        rect_people.x= rect_people.x-10;
        dy=dy+a;
        rect_people.y= rect_people.y+dy;
        draw_game();
    }
    xp=rect_people.x;
    draw_game();
    return rect_people.x;

}
static int panduan()//判断是否在平台上
{
    if(xp>=(blocks[num-2].rect.x-32)&&xp<=(blocks[num-2].rect.x+blockw-18))
    {
        return -1;
    }
    else if(xp>=(blocks[num-1].rect.x-32)&&xp<=(blocks[num-1].rect.x+blockw-25))
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
static void pingyi()
{

    while(rect_people.x<1240)
    {
        rect_people.x+=10;
        blocks[num-2].rect.x+=10;
        blocks[num-1].rect.x+=10;
        draw_game();
    }
    return;

}
static void end()//结束界面,弹出得分和最高分，重置
{
    draw_end();
    printscore1();
    game0=0;
//重置各个量
    blockw=200;//物块宽度
    num=1;//方块个数
    isFiring=0;//空格是否按下，是为1，否为0
    power=0;
    rect_people.x=1240;
    rect_people.y=460;
    zongfen=0;
    zuanshishu=0;
    rect_pingtai1.x=1200;
    rect_pingtai2.x=1200;
    rect_pingtai3.x=1200;
    blocks[0].rect.x=1200;
    return;

}

static void printscore1()//打印end界面字体
{
    sprintf(score1, "%d", zongfen);
    sprintf(b1, "%d", best);
    surface_score1= TTF_RenderUTF8_Blended(font_score1,score1,FontColor);
    texture_score1= SDL_CreateTextureFromSurface(renderer,surface_score1);
    SDL_RenderCopy(renderer,texture_score1,NULL,&rect_score1);

    surface_bests1= TTF_RenderUTF8_Blended(font_bests1,b1,FontColor);
    texture_bests1= SDL_CreateTextureFromSurface(renderer,surface_bests1);
    SDL_RenderCopy(renderer,texture_bests1,NULL,&rect_bests1);

    SDL_RenderPresent(renderer);

}
