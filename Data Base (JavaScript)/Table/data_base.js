(function(){

    let database = new Array();

    let DataBase = {};
    window.DataBase = DataBase;

    DataBase.loadDataBase = load;
    DataBase.saveDataBase = save;

    DataBase.sortData = function(direction, key){
        if((database.lenght <= 0) || (!(key in database[0])) || (key == 'data') || (key == 'name')){
            return false;
        }
        if((direction == undefined) || (direction == null)){
            direction = true;
        }

        let k = true;
        let func = (key == 'counter')? parseInt : parseFloat;
        while(k){
            k = false;
            for(let i = 0; i < (database.length-1); i++){
                let a = func(database[i][key]),
                    b = func(database[i+1][key]);
                if(((direction) && (a < b))
                    || ((!direction) && (a > b))){
                        let temp = Object.assign({}, database[i]);
                        database[i] = database[i+1];
                        database[i+1] = temp;
                        k = true;
                    }
            }
        }

        return true;
    }

    DataBase.setValueToProperty = function(id, key, value){
        if((database.length <= 0) || (typeof key != 'string') 
            || (typeof id != 'number') || (key in database[0])
            || (id <= 0) || (id > database.lenght)){
            return false;
        }

        database[(id-1)][key] = value;
    }
    DataBase.getData = function(){
        return JSON.parse(JSON.stringify(database)); 
    }

    DataBase.getDataSize = function(){
        return database.length;
    }

    DataBase.deleteDataAll = function(){
        if(database.length <= 0){
            return false;
        }

        database.splice(0, database.length);
        return true;
    }

    DataBase.getLastID = function(){
        if(database.length > 0){
            return database[database.length-1].id;
        }

        return 1;
    }

    DataBase.getInformationByID = function(id){
        if(typeof(id) != 'number'){
            throw "Ошибка: попытка взять информацию в базе данных по не известному ID";
        }
        
        load();
        for(let i = 0; i < database.length; i++){
            if(database[i].id == id){
                return JSON.parse(JSON.stringify(database[i]));
            }
        }
 
        throw "Ошибка: не корректный запрос: обращение к элементу таблицы с ID = " + id + ", которого не существует в базе данных";
    }

    DataBase.addInformation = function(data, name, counter, distance){
        if((typeof(data) != 'string') || (typeof(name) != 'string') 
            || (typeof(counter) != 'string') || (typeof(distance) != 'string')){
                throw "Ошибка: попытка передать не корректные данные в таблицу";
            }

        
        let value_id = (database.length > 0)? (database[database.length-1].id + 1) : 1;
        const info = {
            id: value_id,
            data: data,
            name: name,
            counter: counter,
            distance: distance
        };


        database.push(info);
    }

    DataBase.deleteElementByID = function(id){
        if((typeof id != 'number') || (id == undefined) || (id == null)){
            return false;
        }

        for(let i = 0; i < database.length; i++){
            if(parseInt(database[i].id) == id){
                database.splice(i, 1);
                return true;
            }
        }

        return false;
    }
    DataBase.updateID = function(direction){
        if(database.length <= 0){
            return false;
        }
        if((direction == undefined) || (direction == null)){
            directon = true;
        }

        for(let i = 0; i < database.length; i++){
            database[i].id = (direction)? (i+1) : (database.length - i);
        }

        return true;
    }

    function save(){
        localStorage.setItem('db', JSON.stringify(database)); 
    }

    function load(){
        const jsonString = localStorage.getItem('db'); 
        if(jsonString){ 
            database = JSON.parse(jsonString);
            return true;
        }
        return false;
    }


})();