
const tableBody = document.querySelector('[data-table-body]');

const inputs = [document.querySelector('[data-time]'), document.querySelector('[data-name]'),
    document.querySelector('[data-counter]'), document.querySelector('[data-distance]')];

const addButton     = document.querySelector('[data-button-add]');
const saveButton    = document.querySelector('[data-button-save]');
const loadButton    = document.querySelector('[data-button-load]');
const deleteButton  = document.querySelector('[data-button-delete]');
const changeButton  = document.querySelector('[data-button-change]');
const sortButton    = document.querySelector('[data-button-sort]');

const localClear = Object.assign(localStorage.clear);

localStorage.clear = function(){
    localClear.call(localStorage);
    const tdArrays = tableBody.querySelectorAll('tr');
    const trSize = tdArrays.length;

    for(let i = 2; i < trSize; i++){
        tableBody.removeChild(tdArrays[i]);
    }

    window.DataBase.deleteDataAll();
}

function checkDataTime(datatime){
    if((typeof(datatime) != 'string')){
        return false;
    }

    let point = 0;
    for(let i = 1; i < (datatime.length-1); i++){
        if(!('0123456789.'.includes(datatime[i]))){
            return false;
        }
        
        if(datatime[i] == '.'){
            point++;
        }
        
        if(((datatime[i] == datatime[i+1]) || (datatime[i] == datatime[i-1])) && (datatime[i] == '.')){
            return false;
        }
    }

    let numbers = datatime.split('.');
    if((parseInt(numbers[0]) == 0) || (parseInt(numbers[0]) > 31)
        || (parseInt(numbers[1]) > 12) || (parseInt(numbers[1]) == 0)
        || (parseInt(numbers[2]) == 0)){
            return false;
        }

    return ((point == 2) && (('0123456789'.includes(datatime[0])) && ('0123456789'.includes(datatime[datatime.length-1]))));
}

function checkNaturalValue(value){
    if(typeof(value) == 'number'){
        return true;
    }else if(typeof(value) != 'string' && typeof(value) != 'number'){
        return false;
    }

    for(let i = 0; i < value.length; i++){
        if(!('0123456789'.includes(value[i]))){
            return false;
        }
    }
    return true;
}

function checkFloatValue(value){
    if(typeof(value) == 'number'){
        return true;
    }else if(typeof(value) != 'string' && typeof(value) != 'number'){
        return false;
    }

    let k = 0;
    let points = 0;
    for(let i = 0; i < value.length; i++){
        if(((!('0123456789'.includes(value[i]))) && (value[i] != '.'))
            || ((!('0123456789'.includes(value[i]))) && (value[i] == '.') && (i <= 0))){
                return false;
        }

        if(value[i] == '.'){
            points++;
        }
    }

    return (points <= 1);
}
addButton.addEventListener('click', function(event){
    for(let i = 0; i < inputs.length; i++){
        if((inputs[i].value == '') || (inputs[i].value.length <= 0)){
            alert("Заполните все ячейки таблицы!");
            return false;
        }
    }

    if(!checkDataTime(inputs[0].value)){
        alert("Введите дату в формате дд.мм.гг");
        return false;
    }
    if(!checkNaturalValue(inputs[2].value)){
        alert("Введите число корректное натуральное число, характеризющее количество");
        return false;
    }
    if(!checkFloatValue(inputs[3].value)){
        alert("Введите корректное действительное число, характеризующее расстояние");
        return false;
    }

    window.DataBase.addInformation(inputs[0].value, inputs[1].value, inputs[2].value, inputs[3].value);
    
    const tdTable1 = document.createElement('td');
    tdTable1.textContent = window.DataBase.getLastID();
    tdTable1.addEventListener('click', function(event){
        this.style.backgroundColor = (this.style.backgroundColor == 'black')? 'rgb(40, 40, 82)' : 'black';
    });
    const trTable = document.createElement('tr');

    trTable.appendChild(tdTable1);
    for(let i = 0; i < inputs.length; i++){
        const tdTable = document.createElement('td');
        tdTable.textContent = inputs[i].value;
        tdTable.addEventListener('click', function(event){
            this.style.backgroundColor = (this.style.backgroundColor == 'black')? 'rgb(40, 40, 82)' : 'black';
        });
        trTable.appendChild(tdTable);
    }

    tableBody.appendChild(trTable);
    
    for(let i = 0; i < inputs.length; i++){
        inputs[i].value = '';
    }

    return true;
});

saveButton.addEventListener('click', function(event){
    if(window.DataBase.getDataSize() <= 0){
        alert("Данных для сохранения нет!");
        return false;
    }
    window.DataBase.saveDataBase();
    alert("Данные сохранены");
});

loadButton.addEventListener('click', function(event){
    if((!window.DataBase.loadDataBase()) || (window.DataBase.getData().length <= 0)){
        alert("Данных для загрузки нет!");
        return false;
    }

    const tdArrays = tableBody.querySelectorAll('tr');
    const trSize = tdArrays.length;

    for(let i = 2; i < trSize; i++){
        tableBody.removeChild(tdArrays[i]);
    }


    let dat = window.DataBase.getData();
    let trTable = new Array();
    for(let i = 0; i < dat.length; i++){
        trTable.push(document.createElement('tr'));
        let tdArrays = new Array();
        for(let key in dat[i]){
            tdArrays.push(document.createElement('td'));
            tdArrays[tdArrays.length-1].addEventListener('click', function(event){
                this.style.backgroundColor = (this.style.backgroundColor == 'black')? 'rgb(40, 40, 82)' : 'black';
            });
            tdArrays[tdArrays.length-1].textContent = dat[i][key];
        }
        for(let k of tdArrays){
            trTable[trTable.length-1].appendChild(k);
        }
        tableBody.appendChild(trTable[trTable.length-1]);
    }

    alert("Загрузка данных завершена!");
    return true;
});

deleteButton.addEventListener('click', function(event){
    let trTableArray = tableBody.querySelectorAll('tr');
    if(trTableArray.length <= 1){
        alert("Нет данных для удаления!");
        return false;
    }

    let count = 0;
    for(let i = 1; i < trTableArray.length; i++){
        if(trTableArray[i].querySelectorAll('td')[0].style.backgroundColor == 'black'){
            window.DataBase.deleteElementByID(parseInt(trTableArray[i].querySelectorAll('td')[0].textContent));
            count++;
        }
    }

    if(!count){
        alert("Не выделено ни одной строки для удаления!");
        return false;
    }
    window.DataBase.updateID(true);

    const tdArrays = tableBody.querySelectorAll('tr');
    const trSize = tdArrays.length;

    for(let i = 2; i < trSize; i++){
        tableBody.removeChild(tdArrays[i]);
    }

    let dat = window.DataBase.getData();
    let trTable = new Array();
    for(let i = 0; i < dat.length; i++){
        trTable.push(document.createElement('tr'));
        let tdArrays = new Array();
        for(let key in dat[i]){
            tdArrays.push(document.createElement('td'));
            tdArrays[tdArrays.length-1].addEventListener('click', function(event){
                this.style.backgroundColor = (this.style.backgroundColor == 'black')? 'rgb(40, 40, 82)' : 'black';
            });
            tdArrays[tdArrays.length-1].textContent = dat[i][key];
        }
        for(let k of tdArrays){
            trTable[trTable.length-1].appendChild(k);
        }
        tableBody.appendChild(trTable[trTable.length-1]);
    }

});

changeButton.addEventListener('click', function(event){
    let trArray = tableBody.querySelectorAll('tr');
    if((window.DataBase.getDataSize() <= 0) || (trArray.length <= 1)){
        alert("Нет данных для изменения");
    }

    for(let k = 1; k <= 4; k++){
        let keys = ['date', 'date', 'counter', 'distance'];
        let functions = [checkDataTime, (item)=>true, checkNaturalValue, checkFloatValue];
        for(let i = 1; i < trArray.length; i++){
            let td = trArray[i].querySelectorAll('td')[k];
            if((td.style.backgroundColor == 'black') && (inputs[(k-1)].value.length >= 1) && (functions[(k-1)](inputs[(k-1)].value))){
                td.textContent = inputs[(k-1)].value;
                window.DataBase.setValueToProperty(k, keys[(k-1)], inputs[(k-1)].value);
            }else if((td.style.backgroundColor == 'black') && (inputs[(k-1)].value.length >= 1) && (!(functions[(k-1)](inputs[(k-1)].value)))){
                switch((k-1)){
                    case 0:{
                        alert('Невозможно изменить данные даты, т.к. некорректно введена дата(должен быть формат дд.мм.гг)');
                        break;
                    }
                    case 2:{
                        alert('Невозможно изменить данные количества, т.к. некорректно введено число');
                        break;
                    }
                    case 3:{
                        alert('Невозможно изменить данные расстояния, т.к. некорректно введено действительное число');
                        break;
                    }
                }
            }
            td.style.backgroundColor = 'rgb(40, 40, 82)';
        }

        inputs[(k-1)].value = '';
    }
});

sortButton.addEventListener('click', function(event){
    if((window.DataBase.getDataSize() <= 0)){
        alert('Нет данных для сортировки!');
        return false;
    }

    let sort_column = -1;
    let s = false;
    if((inputs[2].value == 'sort1') || (inputs[2].value == 'сортировать1')){
        sort_column = 0;
        s = true;
    }else if((inputs[2].value == 'sort2') || (inputs[2].value == 'сортировать2')){
        sort_column = 0;
        s = false;
    }else if((inputs[3].value == 'sort1') || (inputs[3].value == 'сортировать1')){
        sort_column = 1;
        s = true;
    }else if((inputs[3].value == 'sort2') || (inputs[3].value == 'сортировать2')){
        sort_column = 1;
        s = false;
    }

    for(let i = 0; i < inputs.length; i++){
        inputs[i].value = '';
    }

    if(sort_column == (-1)){
        alert('Заполните текстовое поле словом sort/сортировка того столбца, по которому необходимо произвести сортировку.'
        + 'сортировать1/sort1 - сортировка по убыванию;   сортировать2/sort2 - сортировка по возрастанию;'
        + '   Сортировка осуществима по двум полям - количество и расстояние');
        return false;
    }

    console.log(window.DataBase.sortData(s, (!sort_column)? 'counter' : 'distance'));
    window.DataBase.updateID(true);

    const tdArrays = tableBody.querySelectorAll('tr');
    const trSize = tdArrays.length;

    for(let i = 2; i < trSize; i++){
        tableBody.removeChild(tdArrays[i]);
    }

    let dat = window.DataBase.getData();
    let trTable = new Array();
    for(let i = 0; i < dat.length; i++){
        trTable.push(document.createElement('tr'));
        let tdArrays = new Array();
        for(let key in dat[i]){
            tdArrays.push(document.createElement('td'));
            tdArrays[tdArrays.length-1].addEventListener('click', function(event){
                this.style.backgroundColor = (this.style.backgroundColor == 'black')? 'rgb(40, 40, 82)' : 'black';
            });
            tdArrays[tdArrays.length-1].textContent = dat[i][key];
        }
        for(let k of tdArrays){
            trTable[trTable.length-1].appendChild(k);
        }
        tableBody.appendChild(trTable[trTable.length-1]);
    }

    return true;
});
