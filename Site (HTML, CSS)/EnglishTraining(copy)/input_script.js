(function(){

    let baseData = new Array();
    
    let inputs = [
        document.querySelector('[input-name]'),
        document.querySelector('[input-email]'),
        document.querySelector('[input-callnumber]')
    ];

    document.baseData = baseData;
    const text = ['Ваше имя:', 'E-mail:', 'Телефон:'];

    for(let i = 0; i < 3; i++){
        inputs[i].addEventListener('focus', function(event){
            if(this.value == text[i]){
                this.value = '';
                return;
            }
        });
        inputs[i].addEventListener('blur', function(event){
            if(this.value != ''){
                return;
            }
            this.value = text[i];
        });
    }

    document.querySelector('[input-button]').addEventListener('click', function(event){
        for(let i = 0; i < 3; i++){
            if(inputs[i].value == text[i]){
                alert('Ошибка! Некоторые поля ввода остались пустыми!');
                return;
            }
        }

        for(const symbol of inputs[0].value){
            if(((symbol < 'A') || (symbol > 'Z'))
                && ((symbol < 'a') || (symbol > 'п'))
                && ((symbol < 'р') || (symbol > 'я'))
                && ((symbol < 'А') || (symbol > 'Я'))
                && (symbol != ' ')){
                    alert('Ошибка! Имя должно содержать только символы алфавита!');
                    return;
                }
        }

        let addr = false;
        for(let i = 0; (i < inputs[1].value.length) && (!addr); i++){
            if(inputs[1].value[i] == '@'){
                addr = true;
            }
        }

        if(addr == false){
            alert('Ошибка! Введён некорректный адрес!');
            return;
        }

        for(const symbol of inputs[2].value){
            if(!('0123456789'.includes(symbol))){
                alert('Ошибка! Некорректный ввод номера телефона!');
                return;
            }
        }
        baseData.push({
            name : inputs[0].value,
            email: inputs[1].value,
            call: inputs[2].value
        });

        alert("Заявка успешно оформлена!");

        for(let i = 0; i < 3; i++){
            inputs[i].value = text[i];
        }
    });

})();