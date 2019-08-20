var M = 6 //max index

function precRound(n) {
    var t = n
    var s
    if (precision)
        t = Math.round(n*precision)/precision
    var s = t.toString()
    var dotp = s.indexOf('.')
    var afterdot = ''
    var r = ''
    if (s.indexOf('e') == -1) {
        if (dotp != -1) {
            afterdot = s.slice(dotp)
            s = s.slice(0, dotp)
            if (precision)
                while (afterdot.length - 1 < Math.log10(precision))
                    afterdot += '0'
        } else if (precision > 1 && typeof(n) == "number") {
            afterdot = '.'
            while (afterdot.length - 1 < Math.log10(precision))
                afterdot += '0'
        }
        while (s.length > 3) {
            var n = s.length%3
            if (n == 0) n = 3
            r += s.slice(0, n)
            s = s.slice(n)
            if (s.length > 0)
                r += "'"
        }
    }
    r += s
    if (r == '') r = '0'
    return r + afterdot
}

function changeCheck(s) {
    document.getElementById(s).checked = !document.getElementById(s).checked
    if (document.getElementById(s).checked)
       delete marked[s]
    else
       marked[s] = 1
    drawTable1()
}

function changeOrd(n) {
    sortOrder[n] = trans[sortOrder[n] + 1]
    for (var i = 0; i <= M; ++i)
        if (i != n)
            sortOrder[i] = 0
    drawTable1()
}

function sortCompare(a, b, i) {
    var k = i
    while (typeof(a[i]) == "string" && i > 0) --i
    if (i == 0 && typeof(b[1]) == "string") return 0
    if (i == 0) return -sortOrder[k]
    while (typeof(b[i]) == "string" && i > 0) --i
    if (i == 0) return sortOrder[k]
    return (a[i] - b[i])*sortOrder[k]
}

function getTa(data) {
    var ta = []
    var sortm
    for (sortm in data[order[0]][type[0]]) {
        var el = [ sortm ]
        for (var k = 0; k < M + 2; ++k)
            el.push(data[order[0]][type[0]][sortm][k])
        ta.push(el)
    }
    if (sortOrder[0] != 0)
        ta.sort(function(a, b){ if (a[0] > b[0]) return sortOrder[0]; if (a[0] < b[0]) return -sortOrder[0]; return 0 })
    for (i = 1; i <= M; ++i)
        if (sortOrder[i] != 0)
            ta.sort(function(a, b){ return sortCompare(a, b, i) })
    return ta
}

function drawTable1() {
    var i
    var text = "<tr><th rowspan=2>#<th rowspan=2>Алгоритм<button onclick=changeOrd(0) style='padding:0px 0px;margin:0px 5px'>" + orderArrows[sortOrder[0] + 1]
        + "</button><th colspan=" + M + ">Размер данных" + "<th align=center rowspan=2>Временная<br>зaвиcимocть"
    text += "<tr>"
    for (i = 0; i < M; ++i)
        text += "<th align=center>10<sup>" + (i + 3)
            + "</sup><button onclick=changeOrd(" + (i + 1)
            + ") style='padding:0px 0px;margin:0px 5px'>" + orderArrows[sortOrder[i + 1] + 1] + "</button>"
    var n = 0
    var ta = getTa(Data1)
    var os = document.getElementById("optionSel").value
    for (i = 0; i < ta.length; i++) {
        if (typeof(ta[i][1]) == "number" && (os == 0 || os == 1 && ta[i][0] in marked || os == 2 && i < 7 || os > 2 && indexSorted[os - 3].indexOf(ta[i][0]) != -1)) {
            text += "<tr><td align=center>" + (++n) + "<input id=" + ta[i][0] + " type=checkbox "
            if (ta[i][0] in marked) text += "checked "
            text += "onclick=changeCheck(\"" + ta[i][0] + "\")><td>" + ta[i][0]
            for (var k = 0; k < M; ++k) {
                text += "<td align=right>"
                var a = ta[i][k + 1]
                if (typeof(a) == "number")
                    text += precRound(a)
                else
                    text += a
            }
            var precision_saved = precision
            precision = 1
            var t = ta[i][M + 2]
            while (t*precision < 1 && t != 0) precision *= 10
            text += "<td align=center>" + precRound(ta[i][M + 2]) + "&nbsp;<i>N</i><sup>"
            precision = 100
            text += precRound(ta[i][M + 1]) + "</sup>"
            precision = precision_saved
        }
    }
    document.getElementById("tab1").innerHTML = text
}

function DataAvg() {
    var sum = 0
    var cnt = 0
    var ta = getTa(Data)
    var os = document.getElementById("optionSel").value
    for (var k = 0; k < ta.length; k++) {
        var sortm = ta[k][0]
        for (var i = 1; i <= M; ++i) {
            if (typeof(ta[k][i]) == "number" && (os == 0 || os == 1 && sortm in marked || os == 2 && k < 7 || os > 2 && indexSorted[os - 3].indexOf(sortm) != -1)) {
                sum += ta[k][i]
                cnt++
            }
        }
    }
    return sum/cnt
}

function DataMedian() {
    var ta = getTa(Data)
    var vector = []
    var os = document.getElementById("optionSel").value
    for (var k = 0; k < ta.length; k++) {
        var sortm = ta[k][0]
        for (var i = 1; i <= M; ++i)
            if (typeof(ta[k][i]) == "number" && (os == 0 || os == 1 && sortm in marked || os == 2 && k < 7 || os > 2 && indexSorted[os - 3].indexOf(sortm) != -1))
                vector.push(ta[k][i])
    }
    vector.sort(function(a, b){ if (typeof(a) == "string") return 1; if (typeof(b) == "string") return -1; return a - b })
    return vector[Math.round(vector.length/2)]
}

function DataMin() {
    var min = 1 << 30
    var ta = getTa(Data)
    var os = document.getElementById("optionSel").value
    for (var k = 0; k < ta.length; k++) {
        var sortm = ta[k][0]
        for (var i = 1; i <= M; ++i)
            if (typeof(ta[k][i]) == "number" && (os == 0 || os == 1 && sortm in marked || os == 2 && k < 7 || os > 2 && indexSorted[os - 3].indexOf(sortm) != -1) && ta[k][i] < min)
                min = ta[k][i]
    }
    return min
}

function DataMax() {
    var max = 0
    var ta = getTa(Data)
    var os = document.getElementById("optionSel").value
    for (var k = 0; k < ta.length; k++) {
        var sortm = ta[k][0]
        for (var i = 1; i <= M; ++i)
            if (typeof(ta[k][i]) == "number" && (os == 0 || os == 1 && sortm in marked || os == 2 && k < 7 || os > 2 && indexSorted[os - 3].indexOf(sortm) != -1) && ta[k][i] > max)
                max = ta[k][i]
    }
    return max
}

function changeOptRel() {
    var pivot = 1  //absolute
    optionRel = document.getElementById("optionRel").value
    if (optionRel == 1)  //average
        pivot = DataAvg();
    else if (optionRel == 2)  //median
        pivot = DataMedian();
    else if (optionRel == 3)  //minimum
        pivot = DataMin();
    else if (optionRel == 4)  //maximum
        pivot = DataMax();
    for (var sortm in Data[order[0]][type[0]]) {
        for (var i = 0; i < M; ++i)
            if (typeof(Data[order[0]][type[0]][sortm][i]) == "number")
               Data1[order[0]][type[0]][sortm][i] = Data[order[0]][type[0]][sortm][i]/pivot
        Data1[order[0]][type[0]][sortm][M] = Data[order[0]][type[0]][sortm][M]
        Data1[order[0]][type[0]][sortm][M + 1] = Data[order[0]][type[0]][sortm][M + 1]
    }
    drawTable1()
}

function changeOptPrec() {
    if (document.getElementById("optionsPrec").value < 4)
        precision = Math.pow(10, document.getElementById("optionsPrec").value);
    else
        precision = 0
    drawTable1()
}

function types(n, m) {
    if (n == 1) return type[m]
    return order[m]
}

function drawActionTable1() {
    var sv
    var indexValues = [Data1, Data1[order[0]]] //Sort them!
    var text = ""

    for (var i = 0; i < 2; i++) {
        text += "<br><button id=sbutt" + i + " onclick=changeRow(" + i + ")>" + sbuttc[duoMode[i]] + "</button>:"
        text += "<select id=select" + i + "0 onchange=changeAction(" + i + ",0) style=width:14em>"
        for (sv in indexValues[i]) {
            text += "<option value=" + sv
            if (sv == types(i, 0))
                text += " selected"
            text += ">" + sv + "</option>"
        }
        text += "</select>"

        if (duoMode[i] == 1) {
            text += " / "
            text += "<select id=select" + i + "1 onchange=changeAction(" + i + ",1) style=width:14em>";
            for (sv in indexValues[i]) {
                text += "<option value=" + sv
                if (sv == types(i, 1))
                    text += " selected"
                text += ">" + sv + "</option>"
            }
            text += "</select>"
        }
    }
    document.getElementById("tab1a").innerHTML = text
    if (duoMode[0] + duoMode[1] == 0) { 
        text = "relation: <select id=optionRel onchange=changeOptRel()>"
        for (var i = 0; i < cmpType.length; ++i) {
            text += "<option value=" + i
            if (i == optionRel)
                text += " selected"
            text += ">" + cmpType[i] + "</option>"
        }
        text += "</select>"
    } else
        text = ""
    document.getElementById("rel").innerHTML = text
}

function changeOptAll() {
    if (duoMode[0] > 0) {
        for (var sortm in Data1[order[0]][type[0]]) {
            for (var i = 0; i < M; ++i)
                if (typeof(Data[order[0]][type[0]][sortm][i]) == "number" && typeof(Data[order[1]][type[0]][sortm][i]) == "number")
                    Data1[order[0]][type[0]][sortm][i] = Data[order[0]][type[0]][sortm][i]/Data[order[1]][type[0]][sortm][i]
                else
                    Data1[order[0]][type[0]][sortm][i] = "n/a"
            Data1[order[0]][type[0]][sortm][M] = Data[order[0]][type[0]][sortm][M] - Data[order[1]][type[0]][sortm][M]
            Data1[order[0]][type[0]][sortm][M + 1] = Data[order[0]][type[0]][sortm][M + 1]/Data[order[1]][type[0]][sortm][M + 1]
        }
    } else if (duoMode[1] > 0) {
        for (var sortm in Data1[order[0]][type[0]]) {
            for (var i = 0; i < M; ++i) {
                var b
                if (sortm in Data[order[0]][type[1]])
                    b = Data[order[0]][type[1]][sortm][i]
                else
                    b = 0
                if (b != 0)
                    Data1[order[0]][type[0]][sortm][i] = Data[order[0]][type[0]][sortm][i]/b
                else
                    Data1[order[0]][type[0]][sortm][i] = "n/a"
            }
            Data1[order[0]][type[0]][sortm][M] = Data[order[0]][type[0]][sortm][M] - Data[order[0]][type[1]][sortm][M]
            Data1[order[0]][type[0]][sortm][M + 1] = Data[order[0]][type[0]][sortm][M + 1]/Data[order[0]][type[1]][sortm][M + 1]
        }
    } else
        changeOptRel()
}

function changeRow(n) {
    duoMode[n] = 1 - duoMode[n]
    for (var i = 0; i < 2; ++i)
        if (i != n)
            duoMode[i] = 0
    drawActionTable1()
    changeOptAll()
    drawTable1()
}

function changeAction(n, m) {
    var nms = "select" + n + m.toString()
    if (n == 1)
        type[m] = document.getElementById(nms).value
    else
        order[m] = document.getElementById(nms).value
    changeOptAll()
    drawTable1()
}

