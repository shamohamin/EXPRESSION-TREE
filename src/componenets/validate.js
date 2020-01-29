import validator from 'validator'

export const validate = (rules , data) => {
    let errors = {} ;

    Object.keys(rules).forEach(key => {
        console.log(key)
        let fieldData = data[key] ;
        let field_error = [];

        if(validator.isEmpty(fieldData) && rules[key].empty){
            field_error.push("value required") ;
        }
        if(!validator.isEmpty(fieldData)){
            if(rules[key].num_and_op){
               if(!check(fieldData))
                    field_error.push("must be correct from!!!") ; 
            }
        }
        
        errors[key] = field_error ;
    });

    return errors ;
}

const check = (formula) => {
    let evaluate = true ;
    for(let i of formula)
        if(!(i === '*' || i === '+' || i === '-' || i === '/' || i === ')' || i === '^' || i === '(' || validator.isDecimal(i)))
            evaluate = false ;
    return evaluate ;
}