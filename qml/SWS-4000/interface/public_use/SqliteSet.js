function loadSqliteData(cmd)
{
    var db = LocalStorage.openDatabaseSync("sws4000",3.0,"SWS4000",500000)
    var rs
    db.transaction(function(tx)
                               {
                                    rs = tx.executeSql(cmd)
                                })
    return rs
}
