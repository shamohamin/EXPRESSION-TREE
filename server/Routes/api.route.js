const router = require('express').Router();
const controller = require('../Controller/api');


router.post('/formula' , controller.getData) ;

module.exports = router ;