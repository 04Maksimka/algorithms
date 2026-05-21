#include "glpk.h"
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    glp_term_out(GLP_OFF);

    int n, m;
    std::cin >> n >> m;

    std::vector<double> capacity(n + 1), openCost(n + 1);
    for (int w = 1; w <= n; ++w) {
        std::cin >> capacity[w] >> openCost[w];
    }

    std::vector<double> demand(m + 1);
    for (int c = 1; c <= m; ++c) {
        std::cin >> demand[c];
    }

    std::vector<std::vector<double>> useCost(n + 1, std::vector<double>(m + 1));
    for (int w = 1; w <= n; ++w) {
        for (int c = 1; c <= m; ++c) {
            std::cin >> useCost[w][c];
        }
    }

    glp_prob *lp = glp_create_prob();
    glp_set_obj_dir(lp, GLP_MIN);


    const int total_vars   = n + n * m;
    const int total_constr = m + n;

    glp_add_cols(lp, total_vars);
    glp_add_rows(lp, total_constr);

    // Переменные y_w
    for (int w = 1; w <= n; ++w) {
        glp_set_col_kind(lp, w, GLP_BV);
        glp_set_obj_coef(lp, w, openCost[w]);
    }

    // Переменные x_{w,c}
    for (int w = 1; w <= n; ++w) {
        for (int c = 1; c <= m; ++c) {
            int col = n + (w - 1) * m + c;
            glp_set_col_kind(lp, col, GLP_CV);
            glp_set_col_bnds(lp, col, GLP_DB, 0.0, 1.0);
            glp_set_obj_coef(lp, col, useCost[w][c]);
        }
    }

    for (int c = 1; c <= m; ++c)
        glp_set_row_bnds(lp, c, GLP_FX, 1.0, 1.0);          // клиент c:   = 1
    for (int w = 1; w <= n; ++w)
        glp_set_row_bnds(lp, m + w, GLP_UP, 0.0, 0.0);      // склад w:    <= 0


    const int nnz = n * m + n * (m + 1);
    std::vector<int>    ia(nnz + 1), ja(nnz + 1);
    std::vector<double> ar(nnz + 1);
    int k = 0;

    // (1) sum_w x_{w,c} = 1
    for (int c = 1; c <= m; ++c) {
        for (int w = 1; w <= n; ++w) {
            ++k;
            ia[k] = c;                   
            ja[k] = n + (w - 1) * m + c; 
            ar[k] = 1.0;
        }
    }

    // (2) sum_c demand_c * x_{w,c} - capacity_w * y_w <= 0
    for (int w = 1; w <= n; ++w) {
        for (int c = 1; c <= m; ++c) {
            ++k;
            ia[k] = m + w;              
            ja[k] = n + (w - 1) * m + c;
            ar[k] = demand[c];
        }
        ++k;
        ia[k] = m + w;                  
        ja[k] = w;                      
        ar[k] = -capacity[w];
    }

    glp_load_matrix(lp, nnz, ia.data(), ja.data(), ar.data());

    // Настройки Branch & Cut.
    glp_iocp iocp;
    glp_init_iocp(&iocp);
    iocp.msg_lev  = GLP_MSG_OFF;
    iocp.presolve = GLP_ON;
    iocp.br_tech  = GLP_BR_DTH;
    iocp.bt_tech  = GLP_BT_BLB;
    iocp.pp_tech  = GLP_PP_ALL;
    iocp.gmi_cuts = GLP_ON;
    iocp.mir_cuts = GLP_ON;
    iocp.cov_cuts = GLP_ON;
    iocp.clq_cuts = GLP_ON;
    iocp.fp_heur  = GLP_ON;

    glp_intopt(lp, &iocp);


    std::vector<int> open_w;
    for (int w = 1; w <= n; ++w) {
        if (glp_mip_col_val(lp, w) > 0.5)
            open_w.push_back(w);
    }

    // Вывод.
    std::cout << open_w.size() << '\n';
    for (size_t i = 0; i < open_w.size(); ++i) {
        std::cout << open_w[i] << (i + 1 == open_w.size() ? '\n' : ' ');
    }

    std::cout << std::fixed << std::setprecision(6);
    for (int w : open_w) {
        for (int c = 1; c <= m; ++c) {
            int col = n + (w - 1) * m + c;
            double v = glp_mip_col_val(lp, col);
            if (v < 0) v = 0;
            std::cout << v << (c == m ? '\n' : ' ');
        }
    }

    glp_delete_prob(lp);
    return 0;
}
