-- 2018074657
-- A2
SELECT DISTINCT estadio 
FROM (Local NATURAL JOIN Partidas) 
WHERE ano = 1958;
-- A0
SELECT DISTINCT nome_jogador 
FROM Jogadores 
WHERE numero_camisa = 14;
-- A1
SELECT DISTINCT nome_jogador 
FROM (Jogadores NATURAL JOIN Partidas) 
WHERE iniciais_time = 'ITA'
AND ano = 1994;
-- A8
SELECT DISTINCT estadio 
FROM (local NATURAL JOIN partidas) 
WHERE publico >= 90000;
-- A3
SELECT DISTINCT nome_treinador 
FROM (Jogadores NATURAL JOIN Partidas) 
WHERE gols_mandante >= 7;
-- B7
SELECT DISTINCT nome_treinador, juiz, C.ano
FROM copasdomundo as C
NATURAL JOIN partidas
NATURAL JOIN jogadores 
NATURAL JOIN arbitragem 
WHERE C.campeao = 'Brasil'
AND fase = 'Final'
AND iniciais_time = 'BRA';
-- B4
SELECT COUNT(DISTINCT P.fase), C.campeao
FROM copasdomundo as C, Partidas as P
WHERE C.publico_total > 300000 AND P.ano = C.ano 
GROUP BY C.ano;
-- B6
SELECT time_mandante, ano
FROM Partidas
GROUP BY time_mandante
HAVING COUNT(ano) = 1
ORDER BY ano ASC;
-- B5
SELECT L.cidade, L.estadio, P.publico
FROM Local as L, Partidas as P
WHERE L.id_partida = P.id_partida AND P.ano = 2006 
AND (P.gols_mandante = 3 OR P.gols_visitante = 3);
-- B8
SELECT SUM(gols)
FROM (SELECT gols_visitante as gols
FROM Partidas
WHERE time_visitante = 'Brasil'
AND ano = 2002
UNION ALL
SELECT gols_mandante as gols
FROM Partidas 
WHERE time_mandante = 'Brasil'
AND ano = 2002);