#include "../HeaderFiles/functions.h"
#include "../HeaderFiles/constants.h"
#include "math.h"
#include <time.h>

int tabelcos[90][10] = { 10000, 10000, 10000, 10000, 10000, 10000, 9999, 9999, 9999, 9999, 9998, 9998, 9998, 9997, 9997, 9997, 9996, 9996, 9995, 9995, 9994, 9993, 9993, 9992, 9991, 9990, 9990, 9989, 9988, 9987, 9986, 9985, 9984, 9983, 9982, 9981, 9980, 9979, 9978, 9977, 9976, 9974, 9973, 9972, 9971, 9969, 9968, 9966, 9965, 9963, 9962, 9960, 9959, 9957, 9956, 9954, 9952, 9951, 9949, 9947, 9945, 9943, 9942, 9940, 9938, 9936, 9934, 9932, 9930, 9928, 9925, 9923, 9921, 9919, 9917, 9914, 9912, 9910, 9907, 9905, 9903, 9900, 9898, 9895, 9893, 9890, 9888, 9885, 9882, 9880, 9877, 9874, 9871, 9869, 9866, 9863, 9860, 9857, 9854, 9851, 9848, 9845, 9842, 9839, 9836, 9833, 9829, 9826, 9823, 9820, 9816, 9813, 9810, 9806, 9803, 9799, 9796, 9792, 9789, 9785, 9781, 9778, 9774, 9770, 9767, 9763, 9759, 9755, 9751, 9748, 9744, 9740, 9736, 9732, 9728, 9724, 9720, 9715, 9711, 9707, 9703, 9699, 9694, 9690, 9686, 9681, 9677, 9673, 9668, 9664, 9659, 9655, 9650, 9646, 9641, 9636, 9632, 9627, 9622, 9617, 9613, 9608, 9603, 9598, 9593, 9588, 9583, 9578, 9573, 9568, 9563, 9558, 9553, 9548, 9542, 9537, 9532, 9527, 9521, 9516, 9511, 9505, 9500, 9494, 9489, 9483, 9478, 9472, 9466, 9461, 9455, 9449, 9444, 9438, 9432, 9426, 9421, 9415, 9409, 9403, 9397, 9391, 9385, 9379, 9373, 9367, 9361, 9354, 9348, 9342, 9336, 9330, 9323, 9317, 9311, 9304, 9298, 9291, 9285, 9278, 9272, 9265, 9259, 9252, 9245, 9239, 9232, 9225, 9219, 9212, 9205, 9198, 9191, 9184, 9178, 9171, 9164, 9157, 9150, 9143, 9135, 9128, 9121, 9114, 9107, 9100, 9092, 9085, 9078, 9070, 9063, 9056, 9048, 9041, 9033, 9026, 9018, 9011, 9003, 8996, 8988, 8980, 8973, 8965, 8957, 8949, 8942, 8934, 8926, 8918, 8910, 8902, 8894, 8886, 8878, 8870, 8862, 8854, 8846, 8838, 8829, 8821, 8813, 8805, 8796, 8788, 8780, 8771, 8763, 8755, 8746, 8738, 8729, 8721, 8712, 8704, 8695, 8686, 8678, 8669, 8660, 8652, 8643, 8634, 8625, 8616, 8607, 8599, 8590, 8581, 8572, 8563, 8554, 8545, 8536, 8526, 8517, 8508, 8499, 8490, 8480, 8471, 8462, 8453, 8443, 8434, 8425, 8415, 8406, 8396, 8387, 8377, 8368, 8358, 8348, 8339, 8329, 8320, 8310, 8300, 8290, 8281, 8271, 8261, 8251, 8241, 8231, 8221, 8211, 8202, 8192, 8181, 8171, 8161, 8151, 8141, 8131, 8121, 8111, 8100, 8090, 8080, 8070, 8059, 8049, 8039, 8028, 8018, 8007, 7997, 7986, 7976, 7965, 7955, 7944, 7934, 7923, 7912, 7902, 7891, 7880, 7869, 7859, 7848, 7837, 7826, 7815, 7804, 7793, 7782, 7771, 7760, 7749, 7738, 7727, 7716, 7705, 7694, 7683, 7672, 7660, 7649, 7638, 7627, 7615, 7604, 7593, 7581, 7570, 7559, 7547, 7536, 7524, 7513, 7501, 7490, 7478, 7466, 7455, 7443, 7431, 7420, 7408, 7396, 7385, 7373, 7361, 7349, 7337, 7325, 7314, 7302, 7290, 7278, 7266, 7254, 7242, 7230, 7218, 7206, 7193, 7181, 7169, 7157, 7145, 7133, 7120, 7108, 7096, 7083, 7071, 7059, 7046, 7034, 7022, 7009, 6997, 6984, 6972, 6959, 6947, 6934, 6921, 6909, 6896, 6884, 6871, 6858, 6845, 6833, 6820, 6807, 6794, 6782, 6769, 6756, 6743, 6730, 6717, 6704, 6691, 6678, 6665, 6652, 6639, 6626, 6613, 6600, 6587, 6574, 6561, 6547, 6534, 6521, 6508, 6494, 6481, 6468, 6455, 6441, 6428, 6414, 6401, 6388, 6374, 6361, 6347, 6334, 6320, 6307, 6293, 6280, 6266, 6252, 6239, 6225, 6211, 6198, 6184, 6170, 6157, 6143, 6129, 6115, 6101, 6088, 6074, 6060, 6046, 6032, 6018, 6004, 5990, 5976, 5962, 5948, 5934, 5920, 5906, 5892, 5878, 5864, 5850, 5835, 5821, 5807, 5793, 5779, 5764, 5750, 5736, 5721, 5707, 5693, 5678, 5664, 5650, 5635, 5621, 5606, 5592, 5577, 5563, 5548, 5534, 5519, 5505, 5490, 5476, 5461, 5446, 5432, 5417, 5402, 5388, 5373, 5358, 5344, 5329, 5314, 5299, 5284, 5270, 5255, 5240, 5225, 5210, 5195, 5180, 5165, 5150, 5135, 5120, 5105, 5090, 5075, 5060, 5045, 5030, 5015, 5000, 4985, 4970, 4955, 4939, 4924, 4909, 4894, 4879, 4863, 4848, 4833, 4818, 4802, 4787, 4772, 4756, 4741, 4726, 4710, 4695, 4679, 4664, 4648, 4633, 4617, 4602, 4586, 4571, 4555, 4540, 4524, 4509, 4493, 4478, 4462, 4446, 4431, 4415, 4399, 4384, 4368, 4352, 4337, 4321, 4305, 4289, 4274, 4258, 4242, 4226, 4210, 4195, 4179, 4163, 4147, 4131, 4115, 4099, 4083, 4067, 4051, 4035, 4019, 4003, 3987, 3971, 3955, 3939, 3923, 3907, 3891, 3875, 3859, 3843, 3827, 3811, 3795, 3778, 3762, 3746, 3730, 3714, 3697, 3681, 3665, 3649, 3633, 3616, 3600, 3584, 3567, 3551, 3535, 3518, 3502, 3486, 3469, 3453, 3437, 3420, 3404, 3387, 3371, 3355, 3338, 3322, 3305, 3289, 3272, 3256, 3239, 3223, 3206, 3190, 3173, 3156, 3140, 3123, 3107, 3090, 3074, 3057, 3040, 3024, 3007, 2990, 2974, 2957, 2940, 2924, 2907, 2890, 2874, 2857, 2840, 2823, 2807, 2790, 2773, 2756, 2740, 2723, 2706, 2689, 2672, 2656, 2639, 2622, 2605, 2588, 2571, 2554, 2538, 2521, 2504, 2487, 2470, 2453, 2436, 2419, 2402, 2385, 2368, 2351, 2334, 2317, 2300, 2284, 2267, 2250, 2233, 2215, 2198, 2181, 2164, 2147, 2130, 2113, 2096, 2079, 2062, 2045, 2028, 2011, 1994, 1977, 1959, 1942, 1925, 1908, 1891, 1874, 1857, 1840, 1822, 1805, 1788, 1771, 1754, 1736, 1719, 1702, 1685, 1668, 1650, 1633, 1616, 1599, 1582, 1564, 1547, 1530, 1513, 1495, 1478, 1461, 1444, 1426, 1409, 1392, 1374, 1357, 1340, 1323, 1305, 1288, 1271, 1253, 1236, 1219, 1201, 1184, 1167, 1149, 1132, 1115, 1097, 1080, 1063, 1045, 1028, 1011, 993, 976, 958, 941, 924, 906, 889, 872, 854, 837, 819, 802, 785, 767, 750, 732, 715, 698, 680, 663, 645, 628, 610, 593, 576, 558, 541, 523, 506, 488, 471, 454, 436, 419, 401, 384, 366, 349, 332, 314, 297, 279, 262, 244, 227, 209, 192, 175, 157, 140, 122, 105, 87, 70, 52, 35, 17 };
int tabeltan[90][10] = { 0, 17, 35, 52, 70, 87, 105, 122, 140, 157, 175, 192, 209, 227, 244, 262, 279, 297, 314, 332, 349, 367, 384, 402, 419, 437, 454, 472, 489, 507, 524, 542, 559, 577, 594, 612, 629, 647, 664, 682, 699, 717, 734, 752, 769, 787, 805, 822, 840, 857, 875, 892, 910, 928, 945, 963, 981, 998, 1016, 1033, 1051, 1069, 1086, 1104, 1122, 1139, 1157, 1175, 1192, 1210, 1228, 1246, 1263, 1281, 1299, 1317, 1334, 1352, 1370, 1388, 1405, 1423, 1441, 1459, 1477, 1495, 1512, 1530, 1548, 1566, 1584, 1602, 1620, 1638, 1655, 1673, 1691, 1709, 1727, 1745, 1763, 1781, 1799, 1817, 1835, 1853, 1871, 1890, 1908, 1926, 1944, 1962, 1980, 1998, 2016, 2035, 2053, 2071, 2089, 2107, 2126, 2144, 2162, 2180, 2199, 2217, 2235, 2254, 2272, 2290, 2309, 2327, 2345, 2364, 2382, 2401, 2419, 2438, 2456, 2475, 2493, 2512, 2530, 2549, 2568, 2586, 2605, 2623, 2642, 2661, 2679, 2698, 2717, 2736, 2754, 2773, 2792, 2811, 2830, 2849, 2867, 2886, 2905, 2924, 2943, 2962, 2981, 3000, 3019, 3038, 3057, 3076, 3096, 3115, 3134, 3153, 3172, 3191, 3211, 3230, 3249, 3269, 3288, 3307, 3327, 3346, 3365, 3385, 3404, 3424, 3443, 3463, 3482, 3502, 3522, 3541, 3561, 3581, 3600, 3620, 3640, 3659, 3679, 3699, 3719, 3739, 3759, 3779, 3799, 3819, 3839, 3859, 3879, 3899, 3919, 3939, 3959, 3979, 4000, 4020, 4040, 4061, 4081, 4101, 4122, 4142, 4163, 4183, 4204, 4224, 4245, 4265, 4286, 4307, 4327, 4348, 4369, 4390, 4411, 4431, 4452, 4473, 4494, 4515, 4536, 4557, 4578, 4599, 4621, 4642, 4663, 4684, 4706, 4727, 4748, 4770, 4791, 4813, 4834, 4856, 4877, 4899, 4921, 4942, 4964, 4986, 5008, 5029, 5051, 5073, 5095, 5117, 5139, 5161, 5184, 5206, 5228, 5250, 5272, 5295, 5317, 5340, 5362, 5384, 5407, 5430, 5452, 5475, 5498, 5520, 5543, 5566, 5589, 5612, 5635, 5658, 5681, 5704, 5727, 5750, 5774, 5797, 5820, 5844, 5867, 5890, 5914, 5938, 5961, 5985, 6009, 6032, 6056, 6080, 6104, 6128, 6152, 6176, 6200, 6224, 6249, 6273, 6297, 6322, 6346, 6371, 6395, 6420, 6445, 6469, 6494, 6519, 6544, 6569, 6594, 6619, 6644, 6669, 6694, 6720, 6745, 6771, 6796, 6822, 6847, 6873, 6899, 6924, 6950, 6976, 7002, 7028, 7054, 7080, 7107, 7133, 7159, 7186, 7212, 7239, 7265, 7292, 7319, 7346, 7373, 7400, 7427, 7454, 7481, 7508, 7536, 7563, 7590, 7618, 7646, 7673, 7701, 7729, 7757, 7785, 7813, 7841, 7869, 7898, 7926, 7954, 7983, 8012, 8040, 8069, 8098, 8127, 8156, 8185, 8214, 8243, 8273, 8302, 8332, 8361, 8391, 8421, 8451, 8481, 8511, 8541, 8571, 8601, 8632, 8662, 8693, 8724, 8754, 8785, 8816, 8847, 8878, 8910, 8941, 8972, 9004, 9036, 9067, 9099, 9131, 9163, 9195, 9228, 9260, 9293, 9325, 9358, 9391, 9424, 9457, 9490, 9523, 9556, 9590, 9623, 9657, 9691, 9725, 9759, 9793, 9827, 9861, 9896, 9930, 9965, 10000, 10035, 10070, 10105, 10141, 10176, 10212, 10247, 10283, 10319, 10355, 10392, 10428, 10464, 10501, 10538, 10575, 10612, 10649, 10686, 10724, 10761, 10799, 10837, 10875, 10913, 10951, 10990, 11028, 11067, 11106, 11145, 11184, 11224, 11263, 11303, 11343, 11383, 11423, 11463, 11504, 11544, 11585, 11626, 11667, 11708, 11750, 11792, 11833, 11875, 11918, 11960, 12002, 12045, 12088, 12131, 12174, 12218, 12261, 12305, 12349, 12393, 12437, 12482, 12527, 12572, 12617, 12662, 12708, 12753, 12799, 12846, 12892, 12938, 12985, 13032, 13079, 13127, 13175, 13222, 13270, 13319, 13367, 13416, 13465, 13514, 13564, 13613, 13663, 13713, 13764, 13814, 13865, 13916, 13968, 14019, 14071, 14124, 14176, 14229, 14281, 14335, 14388, 14442, 14496, 14550, 14605, 14659, 14715, 14770, 14826, 14882, 14938, 14994, 15051, 15108, 15166, 15224, 15282, 15340, 15399, 15458, 15517, 15577, 15637, 15697, 15757, 15818, 15880, 15941, 16003, 16066, 16128, 16191, 16255, 16319, 16383, 16447, 16512, 16577, 16643, 16709, 16775, 16842, 16909, 16977, 17045, 17113, 17182, 17251, 17321, 17391, 17461, 17532, 17603, 17675, 17747, 17820, 17893, 17966, 18040, 18115, 18190, 18265, 18341, 18418, 18495, 18572, 18650, 18728, 18807, 18887, 18967, 19047, 19128, 19210, 19292, 19375, 19458, 19542, 19626, 19711, 19797, 19883, 19970, 20057, 20145, 20233, 20323, 20413, 20503, 20594, 20686, 20778, 20872, 20965, 21060, 21155, 21251, 21348, 21445, 21543, 21642, 21742, 21842, 21943, 22045, 22148, 22251, 22355, 22460, 22566, 22673, 22781, 22889, 22998, 23109, 23220, 23332, 23445, 23559, 23673, 23789, 23906, 24023, 24142, 24262, 24383, 24504, 24627, 24751, 24876, 25002, 25129, 25257, 25386, 25517, 25649, 25782, 25916, 26051, 26187, 26325, 26464, 26605, 26746, 26889, 27034, 27179, 27326, 27475, 27625, 27776, 27929, 28083, 28239, 28397, 28556, 28716, 28878, 29042, 29208, 29375, 29544, 29714, 29887, 30061, 30237, 30415, 30595, 30777, 30961, 31146, 31334, 31524, 31716, 31910, 32106, 32305, 32506, 32709, 32914, 33122, 33332, 33544, 33759, 33977, 34197, 34420, 34646, 34874, 35105, 35339, 35576, 35816, 36059, 36305, 36554, 36806, 37062, 37321, 37583, 37848, 38118, 38391, 38667, 38947, 39232, 39520, 39812, 40108, 40408, 40713, 41022, 41335, 41653, 41976, 42303, 42635, 42972, 43315, 43662, 44015, 44373, 44737, 45107, 45483, 45864, 46252, 46646, 47046, 47453, 47867, 48288, 48716, 49152, 49594, 50045, 50504, 50970, 51446, 51929, 52422, 52924, 53435, 53955, 54486, 55026, 55578, 56140, 56713, 57297, 57894, 58502, 59124, 59758, 60405, 61066, 61742, 62432, 63138, 63859, 64596, 65350, 66122, 66912, 67720, 68548, 69395, 70264, 71154, 72066, 73002, 73962, 74947, 75958, 76996, 78062, 79158, 80285, 81443, 82636, 83863, 85126, 86427, 87769, 89152, 90579, 92052, 93572, 95144, 96768, 98448, 100187, 101988, 103854, 105789, 107797, 109882, 112048, 114301, 116645, 119087, 121632, 124288, 127062, 129962, 132996, 136174, 139507, 143007, 146685, 150557, 154638, 158945, 163499, 168319, 173432, 178863, 184645, 190811, 197403, 204465, 212049, 220217, 229038, 238593, 248978, 260307, 272715, 286363, 301446, 318205, 336935, 358006, 381885, 409174, 440661, 477395, 520807, 572900, 636567, 716151, 818470, 954895, 1145887, 1432371, 1909842, 2864777, 5729572 };


float my_sin(float x) {
	//correct
	return sin(x*PI / 180);
}

float my_cos(float x) {
	//correct
	return cos(x*PI / 180);
}

int my_acos(int x) {
	//correct
	return lookup_cos(x);;
}

int my_atan(int x) {
	//correct
	return lookup_tan;
}

int lookup_cos(int x) {
	int hoek = 0;
	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 10; j++) {
			if (tabelcos[i][j] <= waarde) {
				hoek = i * 10 + j;
				return hoek;
			}
		}
	}
}

int lookup_tan(int x) {
	int hoek = 0;
	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 10; j++) {
			if (tabeltan[i][j] >= waarde) {
				hoek = i * 10 + j;
				return hoek;
			}
		}
	}
}

float norm(float x, float y) {
	return (float)sqrt(x*x + y * y);
}
