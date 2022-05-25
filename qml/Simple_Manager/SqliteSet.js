var db

function initdatabase()
{
    db=openDatabaseSync("Simple_Manager",1.0,"simple_manger",100000)
}

function selectdata(name)
{
    var res=""
    if(db)
    {
        db.transaction(
                       function(tx)
                       {
                           var result=tx.executeSql('select Provincial_region_name from Provincial_region')
                            if(result.rows.length>0)
                            {
                                res=result.rows.item(0).value
                            }
                       })
    }
    return res
}
