const _ = require('lodash');
const exec = require('child_process').exec;

const controller = {

    getData : (req , res) => {
        const formula = _.pick(req.body , 'formula') ;
        console.log(req.body) ;
        // console.log(formula.formula);
        exec('chmod u+x cpp_call.sh');
        const myShellScript = exec(`sh ./server/Controller/cpp_call.sh "${formula.formula}"`);
        myShellScript.stdout.on('data', (data) => {
            console.log("hello") ;
            console.log(data)
            res.status(200).send({msg : "everty thing is fucked !!!!"})
        });
        myShellScript.stderr.on('data', (err) => {
            console.log("sdasdasdsadsadasdsadsadasdas");
            console.log(err);    
            res.status(500).send(err) ;
        });
        
    }   
};


module.exports = controller ;