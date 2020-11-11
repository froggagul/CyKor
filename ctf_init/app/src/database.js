const sqlite3=require("sqlite3").verbose()
const db=new sqlite3.Database("users.db", error=>{
    if (error) throw error;
    console.log("Connected to DB.")
})

module.exports= {
    createUser(username, password){
        let query = 'INSERT INTO users(username, password) VALUES(?,?)';
        let stmt = db.prepare(query);
        stmt.run(username, password);
        stmt.finalize();
    },
    getUser(username){
        return new Promise((res,rej)=>{
            db.get(`SELECT username from users where username='${username}'`,(error,data)=>{
                if(error) return rej();
                res(data)
            })
        })
    },
    checkUser(username){
        return new Promise((res, rej) => {
            db.get('SELECT * FROM users WHERE username = ?', username, (error, data) => {
                if (error) return rej();
                res(data === undefined);
            });
        });
    },
    login(username,password){
        return new Promise((res,rej)=>{
            db.get("SELECT username FROM users WHERE username=? AND password=?",username,password,(error,data)=>{
                if(error) rej()
                res(data!==undefined)
            })
        })
    }
}