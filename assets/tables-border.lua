-- tables-border.lua
-- Renders all Markdown pipe tables as full-border LaTeX tabulars.
-- Drop this filter in assets/ and pass it to pandoc via --lua-filter.

local align_map = {
  AlignLeft    = 'l',
  AlignRight   = 'r',
  AlignCenter  = 'c',
  AlignDefault = 'l',
}

-- Render a list of pandoc blocks to a LaTeX string (body only, no preamble).
local function to_latex(blocks)
  local doc = pandoc.Pandoc(blocks)
  return pandoc.write(doc, 'latex'):gsub('%s*\n?$', '')
end

function Table(t)
  -- Build column spec with vertical rules: |l|r|c|...
  local col_spec = '|'
  for _, spec in ipairs(t.colspecs) do
    col_spec = col_spec .. (align_map[spec[1]] or 'l') .. '|'
  end

  local out = {}
  -- Open a group so arraystretch change is scoped to this table
  out[#out+1] = '{\\renewcommand{\\arraystretch}{1.4}\\setlength{\\tabcolsep}{8pt}'
  out[#out+1] = '\\begin{tabular}{' .. col_spec .. '}'
  out[#out+1] = '\\hline'

  -- Header rows (bold)
  if t.head and t.head.rows then
    for _, row in ipairs(t.head.rows) do
      local cells = {}
      for _, cell in ipairs(row.cells) do
        cells[#cells+1] = '\\textbf{' .. to_latex(cell.contents) .. '}'
      end
      out[#out+1] = table.concat(cells, ' & ') .. ' \\\\'
      out[#out+1] = '\\hline'
    end
  end

  -- Body rows
  for _, body in ipairs(t.bodies) do
    for _, row in ipairs(body.body) do
      local cells = {}
      for _, cell in ipairs(row.cells) do
        cells[#cells+1] = to_latex(cell.contents)
      end
      out[#out+1] = table.concat(cells, ' & ') .. ' \\\\'
      out[#out+1] = '\\hline'
    end
  end

  out[#out+1] = '\\end{tabular}}'

  return pandoc.RawBlock('latex', table.concat(out, '\n'))
end