
document.querySelector('html').style.margin = "0";
document.querySelector('body').style.margin = "0";
document.querySelector('body').style.backgroundColor = "rgb(19, 18, 18)";

let header = document.createElement('div');
let global_div = document.createElement('div');
// Элементы верхней части global

let global_header_div = document.createElement('div');
let global_preh_div = document.createElement('div');
let global_db_div = document.createElement('div');
let global_bottom_block; // переключатель
let footer = document.createElement('div');
//global

{
    header.style.height = "40px";
    header.style.backgroundColor = "rgb(39, 37, 37)";
    header.style.margin = "0";
}

{
    global_div.style.backgroundColor = 'white';
    global_div.style.marginLeft = "12%";
    global_div.style.marginRight = "12%";
    global_div.style.height = "1140px";
}

document.body.appendChild(header);
document.body.appendChild(global_div);

{
    const text = ['ГЛАВНАЯ', 'СКИДКИ', 'ГАРАНТИИ', 'ОТЗЫВЫ', 'КАК КУПИТЬ?', 'МОИ ПОКУПКИ', 'КОНТАКТЫ'];
    const srcs = ['https://steamplay.ru/', 'https://steamplay.ru/discounts', 
    'https://steamplay.ru/warranty', 'https://steamplay.ru/reviews',
    'https://steamplay.ru/p', 'https://steamplay.ru/purchase', 'https://steamplay.ru/contacts'];
    const count_block = 7;
    for(let i = 0; i < count_block; i++){
        let block = document.createElement('div');
        block.style.height = header.style.height;
        block.style.width = "auto";
        block.style.display = "inline-block";
        block.style.textAlign = "center";
        block.style.border = '1px solid initial';
        block.style.boxSizing = "border-box";
        block.style.paddingTop = "12px";
        block.style.fontSize = "11px";
        block.style.fontWeight = "bolder";

        let addr = document.createElement('a');
        addr.style.color = 'white';
        addr.style.letterSpacing = '0';
        addr.textContent = text[i];
        addr.style.textDecoration = "none";
        addr.href = srcs[i];

        block.addEventListener('mouseover', function(event){
           block.style.borderBottom = '5px solid rgb(57, 57, 179)'; 
        });

        block.addEventListener('mouseout', function(event){
            block.style.borderBottom = 'none';
        });

        block.appendChild(addr);
        header.appendChild(block);
    }

    let blocks = header.querySelectorAll('div');
    blocks[0].style.marginLeft = '12%';

    for(let i = 1; i < 7; i++){
        blocks[i].style.marginLeft = "2%";
    }

    blocks[5].style.marginLeft = "30%";
}

{
    global_header_div.style.height = "100px";

    for(let i = 0; i < 3; i++){
        let block = document.createElement('div');
        block.style.height = global_header_div.style.height;
        block.style.display = 'inline-block';
        block.style.width = "auto";
        block.style.verticalAlign = 'top';
        block.style.boxSizing = 'border-box';
        global_header_div.appendChild(block);
    }

    let addr = document.createElement('a');
    addr.href="https://steamplay.ru/";
    let image = document.createElement('img');
    image.src = 'image/steamplay.png';
    addr.appendChild(image);

    let blocks = global_header_div.querySelectorAll('div');
    blocks[0].appendChild(addr);
    blocks[0].style.paddingTop = '2%';
    blocks[2].style.paddingTop = '1%';

    let input = document.createElement('input');
    input.type = 'text';
    input.value = 'Что ищем?';
    input.style.borderRadius = '5px';
    input.style.height = '25px';
    input.style.width = '500px';
    input.style.color = 'rgb(83, 83, 88)';
    input.style.marginTop = '7%';

    input.addEventListener('focus', function(event){
        input.value = '';
    });

    input.addEventListener('blur', function(event){
        if(input.value == ''){
            input.value = 'Что ищем?';
            return;
        }

        let b = true;
        for(let i = 0; (i < input.value.length) && b; i++){
            if(input.value[i] != ' '){
                b = false;
            }
        }

        if(b){
            input.value = 'Что ищем?';
        }
    });

    blocks[1].appendChild(input);

    let ul = document.createElement('ul');
    ul.style.listStyleImage = 'url(image/list_image.png)';
    let texts = ['ЛУЧШИЙ МАГАЗИН ИГР', 'МОМЕНТАЛЬНАЯ ДОСТАВКА', 'СКИДКИ И АКЦИИ'];
    for(let i = 0; i < 3; i++){
        let li = document.createElement('li');
        li.style.fontSize = '11px';
        li.textContent = texts[i];
        ul.appendChild(li);
    }

    blocks[2].appendChild(ul);

    for(let i = 1; i < 3; i++){
        blocks[i].style.marginLeft = '2%';
    }
}

global_div.appendChild(global_header_div);

{
    global_preh_div.style.width = global_div.style.width;
    global_preh_div.style.height = '400px';
    for(let i = 0; i < 3; i++){
        let block = document.createElement('div');
        block.style.height = global_preh_div.style.height;
        block.style.display = 'inline-block';
        block.style.verticalAlign = 'top';
        block.style.textAlign = 'center';
        
        global_preh_div.appendChild(block);
    }

    let blocks = global_preh_div.querySelectorAll('div');
    blocks[0].style.width = '200px';

    let texts1 = ['STEAM', 'ORIGIN', 'UPLAY', 'WORLD OF TANKS',
    'WARTHUNDER', 'ИСПЫТАЙ УДАЧУ', 'CS:GO - ОРУЖИЕ', 'WARFACE', 'MINECRAFT', 'ПРОЧЕЕ'];
    let srcs1 = ['https://steamplay.ru/genres/steam', 'https://steamplay.ru/genres/origin',
    'https://steamplay.ru/genres/uplay', 'https://steamplay.ru/genres/wot_account',
    'https://steamplay.ru/genres/warthunder', 'https://steamplay.ru/genres/random',
    'https://steamplay.ru/genres/cs:go_items', 'https://steamplay.ru/genres/warface_account',
    'https://steamplay.ru/genres/minecraft_account', 'https://steamplay.ru/genres/others'];


    blocks[0].appendChild(document.createElement('div'));
    for(let i = 0; i < 10; i++){
        let block = document.createElement('a');
        block.style.display = 'block';
        block.href = srcs1[i];
        block.textContent = texts1[i];
        block.style.margin = '0';
        block.style.height = '35px';
        block.style.fontSize = '12px';
        block.style.fontWeight = 'bolder';
        block.style.paddingTop = '5%';
        block.style.boxSizing = 'border-box';
        block.style.textAlign = 'left';
        block.style.paddingLeft = '15%';
        block.style.textDecoration = 'none';
        block.style.color = 'black';

        block.addEventListener('mouseover', function(event){
            block.style.border = '1px solid rgb(101, 101, 190)';
            block.style.borderLeft = '5px solid rgb(101, 101, 190)';
        });

        block.addEventListener('mouseout', function(event){
            block.style.border = 'none';
        })
        blocks[0].appendChild(block);
    }

    let blocks1 = blocks[0].querySelectorAll('div');
    blocks1[0].textContent = 'РАЗДЕЛЫ';
    blocks1[0].style.textAlign = 'center';
    blocks1[0].style.paddingLeft = '0';
    blocks1[0].style.backgroundColor = 'rgb(101, 101, 190)';
    blocks1[0].style.height = '30px';
    blocks1[0].style.paddingTop = '4%';
    blocks1[0].style.fontSize = '12px';
    blocks1[0].style.fontWeight = 'bolder';
    blocks1[0].style.boxSizing = 'border-box';
    blocks1[0].style.color = 'white';
    blocks1[0].style.marginLeft = '2%';
    blocks1[0].style.marginRight = '2%';
    blocks[0].querySelectorAll('a')[0].style.marginTop = '8%';

    {
        blocks[1].style.width = '610px';
        let header_block = document.createElement('div');
        let bottom_block = document.createElement('div');
        global_bottom_block = bottom_block;

        header_block.style.width = blocks[1].style.width;
        header_block.style.height = '300px';
        header_block.style.display = 'flex';
        header_block.style.flexDirection = 'column-reverse';

        let addr_image = ['image/random.jpg', 'image/dota2_materials.jpg', 'image/ammunation_cs_go.jpg'];
        let text_image = ['Испытай удачу Steam ключ', 'Dota 2 - Вещи', 'Оружие Counter Strike: GO'];
        let price_list = ['от 9 руб.', 'от 15 руб.', 'от 15 руб.'];
        let i = 1;
        header_block.style.backgroundImage = "url(" + addr_image[0] + ')';

        let hb_bottom = document.createElement('div');
        hb_bottom.style.width = blocks[1].style.width;
        hb_bottom.style.height = '40px';
        hb_bottom.style.backgroundColor = "rgb(0, 0, 0, 0.65)";
        hb_bottom.style.order = '1';
        hb_bottom.style.color = 'white';
        hb_bottom.style.textAlign = 'left';
        hb_bottom.style.fontSize = '18px';
        hb_bottom.style.fontWeight = 'bolder';
        hb_bottom.style.boxSizing = 'border-box';
        hb_bottom.style.border = '1px solid initial';

        let text_block = document.createElement('div');
        text_block.style.height = hb_bottom.style.height;
        text_block.style.width = '300px';
        text_block.style.display = 'inline-block';
        text_block.style.verticalAlign = 'top';
        text_block.textContent = text_image[0];
        text_block.style.paddingTop = '10px';
        text_block.style.paddingLeft = '15px';
        text_block.style.boxSizing = 'border-box';

        let red_block = document.createElement('div');
        red_block.style.backgroundColor = 'rgb(172, 34, 172)';
        red_block.style.width = '100px';
        red_block.style.height = '30px';
        red_block.style.display = 'inline-block';
        red_block.style.verticalAlign = 'top';
        red_block.style.marginTop = '5px';
        red_block.style.paddingTop = '4px';
        red_block.style.marginLeft = '31%';
        red_block.style.textAlign = 'center';
        red_block.style.boxSizing = 'border-box';
        red_block.textContent = price_list[0];

        hb_bottom.appendChild(text_block);
        hb_bottom.appendChild(red_block);

        header_block.appendChild(hb_bottom);
        setInterval(function(){
            if(i >= 3){
                i = 0;
            }
            header_block.style.backgroundImage = "url(" + addr_image[i] + ')';
            text_block.textContent = text_image[i];
            red_block.textContent = price_list[i];
            hb_bottom.appendChild(text_block);
            hb_bottom.appendChild(red_block);
            i++;
        }, 10000);

        bottom_block.style.width = blocks[1].style.width;
        bottom_block.style.height = '32px';
        bottom_block.style.marginTop = '10px';

        let texts = ["НОВОЕ", "ЛИДЕРЫ ПРОДАЖ", "ПРЕДЗАКАЗ"];
        let srcs = ['javascript:;', 'javascript:;', 'javascript:;'];

        for(let i = 0; i < 3; i++){
            let block = document.createElement('a');
            block.style.height = bottom_block.style.height;
            block.style.width = '203px';
            block.style.backgroundColor = 'black';
            block.style.color = 'white';
            block.style.fontSize = '12px';
            block.style.textAlign = 'center';
            block.textContent = texts[i];
            block.style.display = "inline-block";
            block.style.verticalAlign = "top";
            block.style.boxSizing = 'border-box';
            block.href = srcs[i];
            block.style.paddingTop = '10px';
            block.style.textDecoration = 'none';

            block.addEventListener('mouseout', function(event){
                this.style.backgroundColor = 'black';
            });

            block.addEventListener('mouseover', function(event){
                this.style.backgroundColor = '#7a7ac4';
            });

            bottom_block.appendChild(block);
        }
        blocks[1].appendChild(header_block);
        blocks[1].appendChild(bottom_block);
        blocks[1].style.marginLeft = '5px';
        blocks[1].style.marginRight = '5px';

    }

    {
        blocks[2].style.width = '168px';

        let texts2 = ['MINECRAFT PREMIUM K', 'MINECRAFT PREMIUM П'
        , 'STEAM КЛЮЧ CS:GO', 'STEAM КЛЮЧ + ПОДАРОК', 
        'СЛУЧАЙНЫЙ КЛЮЧ', 'MINECRAFT PREMIUM', 'COUNTER-STRIKE: GO'
        ,'СЛУЧАЙНЫЙ КЛЮЧ D'];
        blocks[2].appendChild(document.createElement('div'));
        for(let i = 0; i < texts2.length; i++){
            let block = document.createElement('a');
            block.style.display = 'block';
            block.href = srcs1[i];
            block.textContent = texts2[i];
            block.style.margin = '0';
            block.style.height = '35px';
            block.style.fontSize = '11px';
            block.style.fontWeight = 'bolder';
            block.style.paddingTop = '5%';
            block.style.boxSizing = 'border-box';
            block.style.textAlign = 'left';
            block.style.paddingLeft = '12%';
            block.style.textDecoration = 'none';
            block.style.color = 'black';

            block.addEventListener('mouseover', function(event){
                this.style.color = 'rgb(245, 42, 42)';
            });
            block.addEventListener('mouseout', function(event){
                this.style.color = 'black';
            })
            blocks[2].appendChild(block);
        }

        let blocks1 = blocks[2].querySelectorAll('div');
        blocks1[0].textContent = 'ТОП ПРОДАЖ';
        blocks1[0].style.textAlign = 'center';
        blocks1[0].style.paddingLeft = '0';
        blocks1[0].style.backgroundColor = 'rgb(101, 101, 190)';
        blocks1[0].style.height = '30px';
        blocks1[0].style.paddingTop = '4%';
        blocks1[0].style.fontSize = '12px';
        blocks1[0].style.fontWeight = 'bolder';
        blocks1[0].style.boxSizing = 'border-box';
        blocks1[0].style.color = 'white';
        blocks1[0].style.marginLeft = '2%';
        blocks1[0].style.marginRight = '2%';
        blocks[2].querySelectorAll('a')[0].style.marginTop = '8%';
    }
}   

global_div.appendChild(global_preh_div);

{
    global_db_div.style.width = global_div.style.width;
    global_db_div.style.height = '500px';

    for(let i = 0; i < 2; i++){
        let block = document.createElement('div');
        block.style.height = global_db_div.style.height;
        block.style.display = 'inline-block';
        block.style.verticalAlign = 'top';
        block.style.textAlign = 'center';
        
        global_db_div.appendChild(block);
    }

    global_db_div.querySelectorAll('div')[0].style.width = '200px';
    global_db_div.querySelectorAll('div')[1].style.marginLeft = '0.5%';
    global_db_div.querySelectorAll('div')[1].style.width = '783px';
    let db = global_db_div.querySelectorAll('div')[1];

    {
        let texts = ['WARHAMMER 40,000: SPACE MARINE',
        'MINECRAFT PREMIUM [ПОЛНЫЙ ДОСТУП + СМЕНА ДАННЫХ, СКИНА И НИКА]'];
        let srcs = ['image/space_marine.png', 'image/minecraft.png'];
        let prices = ['29 руб.', '55 руб.'];
        let hrefs = ['https://steamplay.ru/goods/1159429',
        'https://steamplay.ru/goods/1709703'];

        for(let i = 0; i < 2; i++){
            let block = document.createElement('div');
            block.style.backgroundColor = 'rgb(41, 39, 39)';
            block.style.width = '158px';
            block.style.border = '1px solid initial';
            block.style.textAlign = 'left';
            block.style.height = '200px';
            let blocks = new Array(3);
            for(let k = 0; k < blocks.length; k++){
                blocks[k] = document.createElement('a');
                blocks[k].style.display = "block";
                blocks[k].style.textDecoration = "none";
                blocks[k].style.color = "white";
                blocks[k].style.width = block.style.width;
                blocks[k].href = hrefs[i];
            }
            block.style.color = 'white';
            block.style.fontSize = '12px';

            blocks[0].style.backgroundImage = 'url(' + srcs[i] + ')';
            blocks[0].style.height = '75px';
            blocks[1].style.paddingLeft = '5px';
            blocks[1].textContent = texts[i];
            blocks[1].style.marginTop = "10px";
            blocks[2].style.height = '30px';
            blocks[2].style.width = '60px';
            blocks[2].style.backgroundColor = 'rgb(172, 34, 172)';
            blocks[2].textContent = prices[i];
            blocks[2].style.fontSize = '15px';
            blocks[2].style.margin = '10px';
            blocks[2].style.textAlign = 'center';
            blocks[2].style.paddingTop = '5px';
            blocks[2].style.boxSizing = 'border-box';
            
            block.style.marginTop = '20px';
            block.style.marginLeft = "20px";

            for(let k = 0; k < blocks.length; k++){
                block.appendChild(blocks[k]);
            }

            global_db_div.querySelectorAll('div')[0].appendChild(block);
        }
    }

    global_bottom_block.querySelectorAll('a')[0].addEventListener('click', function(event){
        let srcs = ["image/sea_of_thieves.jpg", "image/outer_wilds.jpg", "image/desperadosIII.jpg",
            "image/half_life_alyx.jpg", "image/red_dead_redemption2.jpg", "image/planet_zoo.jpg",
            "image/spyro.jpg", "image/remhant.jpg", "image/code_vein.jpg"];
        let texts = ["SEA OF THIEVES", "OUTER WILDS", "DESPERADOS III",
        "HALF-LIFE: ALYX", "RED DEAD REDEMPRION 2", "PLANET ZOO",
        "SPYRO REIGNITED TRILOGY", "REMHANT: FROM THE ASHES", "CODE VEIN"];

        let hrefs = ['https://steamplay.ru/goods/1983426',
        'https://steamplay.ru/goods/2001036',
        'https://steamplay.ru/goods/1710009',
        'https://steamplay.ru/goods/2027669',
        'https://steamplay.ru/goods/1930094',
        'https://steamplay.ru/goods/2001055',
        'https://steamplay.ru/goods/2746581',
        'https://steamplay.ru/goods/2690858',
        'https://steamplay.ru/goods/2708157'];

        let prices = ['649 руб.', '279 руб.', '2099 руб.',
        '731 руб.', '1717 руб.', '999 руб.',
        '1350 руб.', '700 руб.', '899 руб.'];

        BindBlockData(srcs, texts, hrefs, prices, '10px');
    });

    global_bottom_block.querySelectorAll('a')[1].addEventListener('click', function(event){
        let srcs = ["image/random_min.jpg", "image/gtaV.jpg", "image/counter_strike.jpg",
            "image/minecraft.jpg", "image/red_dead_redemption.jpg", "image/minecraft_new.jpg",
            "image/division2.jpg", "image/far_cry_5.jpg", "image/WOT.jpg"];
        let texts = ["STEAM КЛЮЧ [CS:GO ARMA DAYZ GTA 5 H1Z1 RUST] + ПОДАРКИ",
        "GRAND THEFT AUTO V(GTA5) + ПОДАРКИ", "COUNTER-STRIKE: GLOVAL OFFENSIVE PRIME АККАУНТ + ПОДАРОК",
        "MINECRAFT PREMIUM[ПОЛНАЯ СМЕНА ДАННЫХ + ПОЧТА, 100% ГАРАНТИЯ",
        "RED DEAD REDEMPTION 2(RDR2) + ПОДАРКИ", 
        "MINECRAFT PREMIUM[ПОЛНЫЙ ДОСТУП + СМЕНА ДАННЫХ, СКИНА И НИКА]",
        "TOM CLANCY'S: THE DIVISION 2 + ПОДАРОК",
        "FAR CRY 5 + ПОДАРОК",
        "АККАУНТ WOT ОТ 2Т-50Т БОЁВ БЕЗ ПРИВЯЗКИ + ПОЧТА + ПОДАРОК"];

        let hrefs = ['https://steamplay.ru/goods/1983426',
        'https://steamplay.ru/goods/2001036',
        'https://steamplay.ru/goods/1710009',
        'https://steamplay.ru/goods/2027669',
        'https://steamplay.ru/goods/1930094',
        'https://steamplay.ru/goods/2001055',
        'https://steamplay.ru/goods/2613634',
        'https://steamplay.ru/goods/2315652',
        'https://steamplay.ru/goods/2044667'];

        let prices = ['30 руб.', '199 руб.', '329 руб.',
        '499 руб.', '385 руб.', '55 руб.',
        '100 руб.', '66 руб.', '60 руб.'];

        BindBlockData(srcs, texts, hrefs, prices);
    });

    global_bottom_block.querySelectorAll('a')[2].addEventListener('click', function(event){
        let srcs = ["image/cyberpunk.jpg"];
        let texts = ["CYBERPUNK 2077"];

        let hrefs = ['https://steamplay.ru/goods/2670350'];

        let prices = ['1899 руб.'];

        BindBlockData(srcs, texts, hrefs, prices, '10px');
    });

function BindBlockData(srcs, texts, hrefs, prices, textPaddingTop){// функция заполнитель
        while(db.querySelectorAll('div').length != 0){
            db.removeChild(db.querySelector('div'));
        }
        if((textPaddingTop == null) || (textPaddingTop == undefined)){
            textPaddingTop = '3px';
        }
        db.style.textAlign = 'left';
        for(let i = 0; i < srcs.length; i++){
            let block = document.createElement('div');
            block.style.width = '250px';
            block.style.height = '155px';
            block.style.display = 'inline-block';
            block.style.margin = '4px';
            block.style.marginBottom = "0";
            block.style.boxSizing = 'border-box';
            block.style.verticalAlign = 'top';

            let blocks = [document.createElement('a'), document.createElement('div')];
            blocks[0].style.display = 'block';
            blocks[0].href = srcs[i];
            blocks[0].style.backgroundImage = 'url(' + srcs[i] + ')';
            blocks[0].style.height = '117px';
            blocks[0].style.width = block.style.width;
            blocks[0].style.textDecoration = 'none';
            blocks[0].style.color = 'black';
            blocks[0].style.boxSizing = 'border-box';

            let block_price = document.createElement('div');
            block_price.style.backgroundColor = "rgb(172, 34, 172)";
            block_price.style.height = '30px';
            block_price.style.width = '90px';
            block_price.textContent = prices[i];
            block_price.marginTop = '0';
            block_price.style.boxSizing = 'border-box';
            block_price.style.textDecoration = 'none';
            block_price.href = 'none';
            block_price.style.marginLeft = "64%";
            block_price.style.textAlign = 'center';
            block_price.style.paddingTop = '5px';
            block_price.style.color = 'white';
            block_price.style.fontWeight = 'bolder';
            
            blocks[0].appendChild(block_price);

            blocks[1].style.height = '38px';
            blocks[1].style.width = '250px';
            blocks[1].style.color = 'black';
            blocks[1].style.border = '1px solid rgb(102, 100, 100)';
            blocks[1].style.textAlign = 'left';
            blocks[1].style.paddingLeft = '5px';
            blocks[1].style.paddingTop = textPaddingTop;
            blocks[1].appendChild(document.createElement('a'));
            blocks[1].querySelector('a').textContent = texts[i];
            blocks[1].querySelector('a').href = hrefs[i];
            blocks[1].querySelector('a').style.color = 'black';
            blocks[1].querySelector('a').style.textDecoration = 'none';
            blocks[1].querySelector('a').addEventListener('mouseover', function(event){
                this.style.textDecoration = 'none';
                this.style.color = 'rgb(77, 77, 216)';
            });
            blocks[1].querySelector('a').addEventListener('mouseout', function(event){
                this.style.color = 'black';
            });
            blocks[1].style.boxSizing = 'border-box';
            blocks[1].style.fontSize = '12px';

            block.appendChild(blocks[0]);
            block.appendChild(blocks[1]);
            db.appendChild(block);
        }
    }

}

global_div.appendChild(global_db_div);

{
    footer.style.height = '140px';
    footer.style.boxSizing = 'border-box';
    footer.style.width = 'inherit';
    footer.style.backgroundColor = 'rgb(29, 28, 28)';
    footer.style.color = 'rgb(66, 63, 63)';
    footer.textContent = '© STEAMPLAY.RU, 2014-2020. - Магазин игр. Купить ключ стим или аккаунт Steam, Origin, Uplay, World of Tanks, Warface, Minecraft дешево.'
    +'Этот сайт не был одобрен корпорацией Valve и не аффилирован с корпорацией Valve или ее лицензиаров.'
    +'Все продаваемые ключи закупаются у официальных дилеров, работающих напрямую с издателями: 1С, Бука, Новый Диск и Electronic Arts.';
    footer.style.paddingLeft = "20px";
    footer.style.paddingTop = '4%';
}

global_div.appendChild(footer);