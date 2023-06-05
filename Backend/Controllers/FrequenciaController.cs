using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using SME.Models;
using SME.Repository;

namespace SME.Controllers;

[ApiController]
[Route("[controller]")]
public class FrequenciaController : ControllerBase
{
    private readonly SmeDbContext _dbContext;

    public FrequenciaController(SmeDbContext dbContext)
    {
        _dbContext = dbContext;
    }


    [HttpPost]
    public async Task<IActionResult> Create(Frequencia frequencia)
    {
        frequencia.Data = DateTime.Now;
        await _dbContext.Frequencias.AddAsync(frequencia);
        var result = await _dbContext.SaveChangesAsync();
        if(result > 0)
            return Ok();
        return BadRequest();
    }
    
    [HttpGet]
    public async Task<IActionResult> GetFrequencia()
    {
        var frequenciaAtual = await _dbContext.Frequencias.OrderByDescending(f => f.Data).FirstOrDefaultAsync();
        return Ok(frequenciaAtual);
    }
}